prev build works on 1.5.97, 1.6.64, and VR. On 1.6+ when used with TDM there is a guaranteed crash due to both plugins accessing same memory address. possibly this is due to a new issue with tdm, or could just be a change in the game itself changing the addresses needed here and by coincidence the old incorrect address is a valid address tdm by coincidence uses. either way needs an update and needed some refactoring. Unfortunately I have had terrible success trying to build SKSE/CLib plugins so not sure when an update will happen

# BunnyHopperOfSkyrim-NG

## Build Dependencies
* ~[Json2Settings](https://github.com/Ryan-rsm-McKenzie/Json2Settings)~ Now included as header-only library
* [CommonLibSSE-NG](https://github.com/CharmedBaryon/CommonLibSSE-NG)

## End User Dependencies
* [SKSE64](https://skse.silverlock.org/)
* [Address Library](https://www.nexusmods.com/skyrimspecialedition/mods/32444)

## Settings
Setting | Type | Default | Description
--- | --- | --- | ---
`globalSpeedMult` | float | 1.0 | Global speed multiplier
`maxSpeed` | float | 450.0 | Maximum speed allowed
`misstepAllowed` | int | 4 | Missteps allowed to take before losing all speed
`baseSpeedBoost` | float | 1.0 | Base speed gain after each consecutive jump
`baseSpeedMult` | float | 1.0 | Base speed gain multiplier
`minStrafeAngle` | float | 35.0 | Minimum profitable strafe angle threshold
`maxStrafeAngle` | float | 95.0 | Maximum profitable strafe angle cap
`strafeDeadzone` | float | 35.0 | Non-profitable strafe angle range
`strafeSpeedMult` | float | 0.5 | Speed gain multiplier after each successful strafe
`minHeightLaunch` | float | 140.0 | Minimum landing height to gain a launch boost
`heightLaunchMulti` | float | 0.5 | Speed gain multiplier after each successful height launch
`crouchSpeedBoost` | float | 32.0 | Speed gain for crouching during landing
`crouchSpeedMult` | float | 1.0 | Speed gain multiplier after a successful crouch boost
`crouchBoostCooldown` | int | 6 | Number of successful jumps required to regain crouch boost
`ramDamage` | float | 5.0 | Base damage dealt when ramming objects when bhopping
`ramDamageMult` | float | 0.3 | Ram damage multiplier based on current speed
`ramSpeedThreshold` | float | 220.0 | Minimum speed required to initiate ram
`ramSpeedReduction` | float | 0.5 | Speed loss multiplier after ramming
`enableJumpFeedback` | bool | true | Toggle overall jump feedback functionality
`enableFovZoom` | bool | true | Enable the fov zoom effect for jump feedback
`enableTremble` | bool | false | Enable the screen tremble effect for jump feedback (causes visual artifacts)
