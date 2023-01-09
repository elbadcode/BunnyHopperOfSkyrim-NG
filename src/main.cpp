#include "Events.h"
#include "version.h"
#include "Strafe.h"
#include "Settings.h"

#include "RE/Skyrim.h"
#include "SKSE/API.h"


namespace
{
	class TESObjectLoadedHandler final : public RE::BSTEventSink<RE::TESObjectLoadedEvent>
	{
	public:
		using EventResult = RE::BSEventNotifyControl;


		static TESObjectLoadedHandler* GetSingleton()
		{
			static TESObjectLoadedHandler singleton;
			return std::addressof(singleton);
		}


		auto ProcessEvent(const RE::TESObjectLoadedEvent* a_event, RE::BSTEventSource<RE::TESObjectLoadedEvent>* a_eventSource)
		-> EventResult override
		{
			if (!a_event) {
				return EventResult::kContinue;
			}

			const auto player = RE::PlayerCharacter::GetSingleton();
			if (a_event->formID == player->formID) {
				AnimationGraphEventHandler(Events::BHopHandler::GetSingleton());
			}

			return EventResult::kContinue;
		}

		TESObjectLoadedHandler(const TESObjectLoadedHandler&) = delete;
		TESObjectLoadedHandler(TESObjectLoadedHandler&&) = delete;

		TESObjectLoadedHandler& operator=(const TESObjectLoadedHandler&) = delete;
		TESObjectLoadedHandler& operator=(TESObjectLoadedHandler&&) = delete;

	protected:
		TESObjectLoadedHandler() = default;
		virtual ~TESObjectLoadedHandler() = default;
	};


	void MessageHandler(SKSE::MessagingInterface::Message* a_msg)
	{
		switch (a_msg->type) {
		case SKSE::MessagingInterface::kDataLoaded:
			{
				auto sourceHolder = RE::ScriptEventSourceHolder::GetSingleton();
				sourceHolder->AddEventSink<RE::TESObjectLoadedEvent>(TESObjectLoadedHandler::GetSingleton());
			}
			break;
		default: ;
		}
	}
}

void InitializeLogging() {
    auto path = logger::log_directory();
    if (!path) {
        util::report_and_fail("Unable to lookup SKSE logs directory.");
    }
    *path /= SKSE::PluginDeclaration::GetSingleton()->GetName();
    *path += L".log";

    std::shared_ptr<spdlog::logger> log;
    if (IsDebuggerPresent()) {
        log = std::make_shared<spdlog::logger>("Global", std::make_shared<spdlog::sinks::msvc_sink_mt>());
    } else {
        log = std::make_shared<spdlog::logger>(
            "Global", std::make_shared<spdlog::sinks::basic_file_sink_mt>(path->string(), true));
    }
    log->set_level(spdlog::level::level_enum::info);
    log->flush_on(spdlog::level::level_enum::trace);

    spdlog::set_default_logger(std::move(log));
    spdlog::set_pattern("%s(%#): [%l] %v");
}


SKSEPluginLoad(const SKSE::LoadInterface* a_skse)
{
  InitializeLogging();
	logger::info("BunnyHopperOfSkyrim loaded");
	
	Init(a_skse);

	const auto messaging = SKSE::GetMessagingInterface();
	if (messaging->RegisterListener("SKSE", MessageHandler)) {
		logger::info("Messaging interface registration successful");
	} else {
		logger::critical("Messaging interface registration failed!\n");
		return false;
	}

	if (Settings::LoadSettings()) {
		logger::info("Settings successfully loaded");
	} else {
		logger::critical("Settings failed to load!\n");
		return false;
	}

	return true;
}
