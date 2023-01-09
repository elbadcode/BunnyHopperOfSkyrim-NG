#include "Speed.h"
#include "Settings.h"


void SpeedController::Reset() noexcept
{
	Update();

	player->AsActorValueOwner()->SetActorValue(RE::ActorValue::kSpeedMult, baseSpeed);

	currSpeed = baseSpeed;
}


void SpeedController::Update() noexcept
{
	if (baseSpeed == -1) {
		baseSpeed = player->AsActorValueOwner()->GetActorValue(RE::ActorValue::kSpeedMult);
		currSpeed = baseSpeed;
	}

	if (currSpeed > *Settings::maxSpeed) {
		currSpeed = *Settings::maxSpeed;
	}

	player->AsActorValueOwner()->SetActorValue(RE::ActorValue::kSpeedMult, currSpeed);
}


void SpeedController::SpeedUp(const float a_speedOffset)
{
	const float speedBoost = *Settings::globalSpeedMult * *Settings::baseSpeedBoost * *Settings::baseSpeedMult;
	currSpeed += speedBoost + a_speedOffset;
	Update();

	logger::debug("Speed-Speed {}", speedBoost + a_speedOffset);
}
