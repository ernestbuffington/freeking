#include "IEntity.h"
#include <string>
#include <unordered_map>
#include <memory>

#include "Entity/Item/AHealth.h"
#include "Entity/Item/AHealthSmall.h"
#include "Entity/Item/AHealthLarge.h"
#include "Entity/Item/AHealthMega.h"
#include "Entity/Info/APlayerStart.h"
#include "Entity/Info/APlayerDeathmatch.h"
#include "Entity/Info/APlayerCoop.h"
#include "Entity/Info/APlayerIntermission.h"
#include "Entity/Func/APlat.h"
#include "Entity/Func/AButton.h"
#include "Entity/Func/ADoor.h"
#include "Entity/Func/ADoorSecret.h"
#include "Entity/Func/ADoorRotating.h"
#include "Entity/Func/ARotating.h"
#include "Entity/Func/ATrain.h"
#include "Entity/Func/AWater.h"
#include "Entity/Func/AConveyor.h"
#include "Entity/Func/AAreaportal.h"
#include "Entity/Func/AClock.h"
#include "Entity/Func/AWall.h"
#include "Entity/Func/AObject.h"
#include "Entity/Func/ATimer.h"
#include "Entity/Func/AExplosive.h"
#include "Entity/Func/AKillbox.h"
#include "Entity/Func/AObjectRepair.h"
#include "Entity/Rotating/ALight.h"
#include "Entity/Trigger/AAlways.h"
#include "Entity/Trigger/AOnce.h"
#include "Entity/Trigger/AMultiple.h"
#include "Entity/Trigger/ARelay.h"
#include "Entity/Trigger/APush.h"
#include "Entity/Trigger/AHurt.h"
#include "Entity/Trigger/AKey.h"
#include "Entity/Trigger/ACounter.h"
#include "Entity/Trigger/AElevator.h"
#include "Entity/Trigger/AGravity.h"
#include "Entity/Trigger/AMonsterjump.h"
#include "Entity/Target/ATempEntity.h"
#include "Entity/Target/ASpeaker.h"
#include "Entity/Target/AExplosion.h"
#include "Entity/Target/AChangelevel.h"
#include "Entity/Target/ASecret.h"
#include "Entity/Target/AGoal.h"
#include "Entity/Target/ASplash.h"
#include "Entity/Target/ASpawner.h"
#include "Entity/Target/ABlaster.h"
#include "Entity/Target/ACrosslevelTrigger.h"
#include "Entity/Target/ACrosslevelTarget.h"
#include "Entity/Target/ALaser.h"
#include "Entity/Target/ALightramp.h"
#include "Entity/Target/AEarthquake.h"
#include "Entity/Target/ACharacter.h"
#include "Entity/Target/AString.h"
#include "Entity/Target/AMalLaser.h"
#include "Entity/AWorldspawn.h"
#include "Entity/AViewthing.h"
#include "Entity/ALight.h"
#include "Entity/Light/AMine1.h"
#include "Entity/Light/AMine2.h"
#include "Entity/Info/ANull.h"
#include "Entity/Func/AGroup.h"
#include "Entity/Info/ANotnull.h"
#include "Entity/Path/ACorner.h"
#include "Entity/AJunior.h"
#include "Entity/Misc/AExplobox.h"
#include "Entity/Misc/AGibArm.h"
#include "Entity/Misc/AGibLeg.h"
#include "Entity/Misc/AGibHead.h"
#include "Entity/Misc/ATeleporter.h"
#include "Entity/Misc/ATeleporterDest.h"
#include "Entity/Misc/AAmb4.h"
#include "Entity/Cast/APunk.h"
#include "Entity/Cast/AThug.h"
#include "Entity/Cast/AThugSit.h"
#include "Entity/Cast/ABitch.h"
#include "Entity/Cast/ADog.h"
#include "Entity/Cast/ARunt.h"
#include "Entity/Cast/ABumSit.h"
#include "Entity/Cast/AShorty.h"
#include "Entity/Cast/AWhore.h"
#include "Entity/Cast/APunkWindow.h"
#include "Entity/Cast/APunk2.h"
#include "Entity/Cast/ARosie.h"
#include "Entity/Ai/ABoundary.h"
#include "Entity/Ai/AEventHostile.h"
#include "Entity/Ai/AEventFollow.h"
#include "Entity/Ai/AGuard.h"
#include "Entity/Ai/ATerritory.h"
#include "Entity/Ai/ATriggerCharacter.h"
#include "Entity/Ai/ALockedDoor.h"
#include "Entity/Misc/ASkidrowRadio.h"
#include "Entity/Misc/ASkidrowAmbush.h"
#include "Entity/Misc/ASkidrowRadioRepeater.h"
#include "Entity/Ai/ATyFuseblown.h"
#include "Entity/Ai/AMokerNotinoffice.h"
#include "Entity/Misc/AGrunt.h"
#include "Entity/Misc/AFidela.h"
#include "Entity/Misc/ACar.h"
#include "Entity/Misc/ASmoke.h"
#include "Entity/AElps.h"
#include "Entity/Misc/AAlarm.h"
#include "Entity/Trigger/AHurtElectric.h"
#include "Entity/Pawn/AOMatic.h"
#include "Entity/Ai/ASafespot.h"
#include "Entity/Misc/ASkidrowAiReset.h"
#include "Entity/Ai/ACombatSpot.h"
#include "Entity/Misc/ASkidrowAfraid.h"
#include "Entity/Misc/ASteeltownAfraid.h"
#include "Entity/Misc/AKrokerAfraid.h"
#include "Entity/Rc/AInitiationObserver.h"
#include "Entity/Rc/AInitiationBrush.h"
#include "Entity/Misc/APvAfraid.h"
#include "Entity/Misc/ATyAfraid.h"
#include "Entity/Ai/ATyMoBoundry.h"
#include "Entity/Ai/ASyDykesBoundry.h"
#include "Entity/Misc/ASyAfraid.h"
#include "Entity/Ep/ASkidrowFlag.h"
#include "Entity/Ai/ASyOilcan.h"
#include "Entity/Ai/ATyValvehandle.h"
#include "Entity/Ai/APvFuseblown1.h"
#include "Entity/Ai/APvFuseblown2.h"
#include "Entity/Ai/APvDeadlouie.h"
#include "Entity/Ai/ASyBlefty.h"
#include "Entity/Misc/ABarryBitch.h"
#include "Entity/Misc/ACorkyFidelMdxPcx.h"
#include "Entity/Misc/ACorkyFidelMdxTga.h"
#include "Entity/Misc/ACutScene.h"
#include "Entity/Light/AFireEsm.h"
#include "Entity/Light/AFireSm.h"
#include "Entity/Light/AFireMed.h"
#include "Entity/Light/AFireLg.h"
#include "Entity/Smoke/AEsm.h"
#include "Entity/Smoke/ASm.h"
#include "Entity/Smoke/AMed.h"
#include "Entity/Smoke/ALg.h"
#include "Entity/Func/ATrainRotating.h"
#include "Entity/Func/ASubdoorBase.h"
#include "Entity/Func/ASubdoorHandle1.h"
#include "Entity/Func/ASubdoorHandle2.h"
#include "Entity/Props/ATrashcana.h"
#include "Entity/Props/ATrashcanFall.h"
#include "Entity/Props/AHydrant.h"
#include "Entity/Props/AAntenna1a.h"
#include "Entity/Props/AAntenna1b.h"
#include "Entity/Props/AAntenna1c.h"
#include "Entity/Props/AAntenna2a.h"
#include "Entity/Props/AAntenna2b.h"
#include "Entity/Props/AAntenna2c.h"
#include "Entity/Props/AAntenna3a.h"
#include "Entity/Props/AAntenna3b.h"
#include "Entity/Props/AAntenna3c.h"
#include "Entity/Props/AFan.h"
#include "Entity/Props/APhone.h"
#include "Entity/Props/AAircon.h"
#include "Entity/Props/ATableseta.h"
#include "Entity/Props/ARadio.h"
#include "Entity/Cast/ABuma.h"
#include "Entity/Cast/ABumb.h"
#include "Entity/Elements/ARaincloud.h"
#include "Entity/Elements/ASnowcloud.h"
#include "Entity/Misc/ACutsceneTrigger.h"
#include "Entity/Misc/ACutsceneCamera.h"
#include "Entity/Trigger/AUnlock.h"
#include "Entity/Props/AChair.h"
#include "Entity/Props/AExtinguishera.h"
#include "Entity/Props/AExtinguisherb.h"
#include "Entity/Light/ASconce.h"
#include "Entity/Props/AMotorcycle.h"
#include "Entity/Props/AAmmocrateBust.h"
#include "Entity/Props/AShelf.h"
#include "Entity/Props/AMattressa.h"
#include "Entity/Props/AMattressb.h"
#include "Entity/Props/AMattressc.h"
#include "Entity/Trigger/AMotorcycle.h"
#include "Entity/Props/ATv.h"
#include "Entity/Props/ASteamMachine.h"
#include "Entity/Light/ABulb.h"
#include "Entity/Props/ATrash.h"
#include "Entity/Props/AWallFall.h"
#include "Entity/Props/ATrashbottle.h"
#include "Entity/Props/ATrashwall.h"
#include "Entity/Props/ATrashpaper.h"
#include "Entity/Props/ATrashcorner.h"
#include "Entity/Props/ATrashbottleVert.h"
#include "Entity/Props/ABlimp.h"
#include "Entity/Misc/AUseCutscene.h"
#include "Entity/Props/AMotorcycleRunaway.h"
#include "Entity/Trigger/AHurtFire.h"
#include "Entity/Props/AShelfFall.h"
#include "Entity/Target/AFire.h"
#include "Entity/Props/ARat.h"
#include "Entity/Props/ARatSpawner.h"
#include "Entity/Props/ARatSpawnerNode.h"
#include "Entity/Target/AFlamethrower.h"
#include "Entity/Light/ADecoSconce.h"
#include "Entity/Light/APendant.h"
#include "Entity/Props/AShelfbFall.h"
#include "Entity/Func/ALift.h"
#include "Entity/Props/ARoofVent.h"
#include "Entity/Props/ARatTrigger.h"
#include "Entity/Props2/ATruckDie.h"
#include "Entity/Props/AColaMachine.h"
#include "Entity/Props/ACigMachine.h"
#include "Entity/Props2/ABarrelsFalla.h"
#include "Entity/Props2/ABarrelsFallb.h"
#include "Entity/Props2/AClubcouch.h"
#include "Entity/Props2/AClubchair.h"
#include "Entity/Props2/AVasea.h"
#include "Entity/Props2/AVaseb.h"
#include "Entity/Props2/AChairConf.h"
#include "Entity/Props2/AShelfMetalAFall.h"
#include "Entity/Props2/AShelfMetalBFall.h"
#include "Entity/Props2/ADeadguy.h"
#include "Entity/Props2/AChairPush.h"
#include "Entity/Props/ACrateBust32.h"
#include "Entity/Props/ACrateBust48.h"
#include "Entity/Props/ACrateBust64.h"
#include "Entity/Props2/AFlag.h"
#include "Entity/Props2/AFish.h"
#include "Entity/Props2/AFishTrigger.h"
#include "Entity/Props2/AFishSpawner.h"
#include "Entity/Props2/AFishSpawnerNode.h"
#include "Entity/Props2/AWallFish.h"
#include "Entity/Props2/ABarrelsFallSt.h"
#include "Entity/Props2/ASign.h"
#include "Entity/Props2/ALighthouseBeam.h"
#include "Entity/Props2/ABoat.h"
#include "Entity/Props2/ABuoy.h"
#include "Entity/Props2/ABuoySide.h"
#include "Entity/Props2/ADeadguyUnderwater.h"
#include "Entity/Props2/ABuoyAnimate.h"
#include "Entity/Props2/AGargoyle.h"
#include "Entity/Props2/AClothesline.h"
#include "Entity/Props2/APlantXl.h"
#include "Entity/Props2/APlantSm.h"
#include "Entity/Props2/ABoatphone.h"
#include "Entity/Props2/AAshtray.h"
#include "Entity/Props2/ALunch.h"
#include "Entity/Props2/ADeadgalHeadless.h"
#include "Entity/Props2/APlantBush.h"
#include "Entity/Props2/ABoatAnimate.h"
#include "Entity/Props2/AHelicopterAnimate.h"
#include "Entity/Props2/ACarAnimate.h"
#include "Entity/Props2/ACarTopdown.h"
#include "Entity/Props2/ACarTopup.h"
#include "Entity/Props2/APlantFern.h"
#include "Entity/Props2/APinballMachine.h"
#include "Entity/Props2/ABarrelsPvA.h"
#include "Entity/Props2/ABarrelsPvC.h"
#include "Entity/Props2/ABarrelsPvD.h"
#include "Entity/Props2/ABarrelsPvE.h"
#include "Entity/Props2/ABarrelsPvF.h"
#include "Entity/Light/AChandelier.h"
#include "Entity/Props2/AAirTrain.h"
#include "Entity/Props3/ADeadLouie.h"
#include "Entity/Props3/ACutBossPlayerAnimate.h"
#include "Entity/Props3/ADecoFixture.h"
#include "Entity/Props3/ACutBossChickAnimate.h"
#include "Entity/Props3/ACutTrainRunAnimate.h"
#include "Entity/Props3/ACutAAnimate.h"
#include "Entity/Props3/ACutBAnimate.h"
#include "Entity/Props3/ACutCAnimate.h"
#include "Entity/Props3/ACutDAnimate.h"
#include "Entity/Props3/ACashCounterAnimate.h"
#include "Entity/Props2/ABarrelsPvB.h"
#include "Entity/Props3/ADecanter.h"
#include "Entity/Props3/AWhiskeyGlass.h"
#include "Entity/Props3/ABarrelsFallNikkiA.h"
#include "Entity/Props3/ABarrelsFallNikkiB.h"
#include "Entity/Props3/ACutRunToCarAnimate.h"
#include "Entity/Props3/ACutFinalAnimate.h"
#include "Entity/Props3/ACash.h"
#include "Entity/Props3/ACutTruckDriver.h"
#include "Entity/Props3/ACutPinballGuyAnimate.h"
#include "Entity/ALightflare.h"
#include "Entity/Path/ACornerCast.h"
#include "Entity/Pistol/AModDamage.h"
#include "Entity/Pistol/AModRof.h"
#include "Entity/Pistol/AModReload.h"
#include "Entity/Hmg/AModCooling.h"
#include "Entity/Sfx/ABeacon.h"
#include "Entity/ARefl.h"
#include "Entity/Dm/ACashspawn.h"
#include "Entity/Dm/ASafebag.h"
#include "Entity/Dm/APropsBanner.h"

namespace Freeking
{
	shared_ptr_entity make_item_health() { return std::make_shared<Entity::Item::AHealth>(); }
	shared_ptr_entity make_item_health_small() { return std::make_shared<Entity::Item::AHealthSmall>(); }
	shared_ptr_entity make_item_health_large() { return std::make_shared<Entity::Item::AHealthLarge>(); }
	shared_ptr_entity make_item_health_mega() { return std::make_shared<Entity::Item::AHealthMega>(); }
	shared_ptr_entity make_info_player_start() { return std::make_shared<Entity::Info::APlayerStart>(); }
	shared_ptr_entity make_info_player_deathmatch() { return std::make_shared<Entity::Info::APlayerDeathmatch>(); }
	shared_ptr_entity make_info_player_coop() { return std::make_shared<Entity::Info::APlayerCoop>(); }
	shared_ptr_entity make_info_player_intermission() { return std::make_shared<Entity::Info::APlayerIntermission>(); }
	shared_ptr_entity make_func_plat() { return std::make_shared<Entity::Func::APlat>(); }
	shared_ptr_entity make_func_button() { return std::make_shared<Entity::Func::AButton>(); }
	shared_ptr_entity make_func_door() { return std::make_shared<Entity::Func::ADoor>(); }
	shared_ptr_entity make_func_door_secret() { return std::make_shared<Entity::Func::ADoorSecret>(); }
	shared_ptr_entity make_func_door_rotating() { return std::make_shared<Entity::Func::ADoorRotating>(); }
	shared_ptr_entity make_func_rotating() { return std::make_shared<Entity::Func::ARotating>(); }
	shared_ptr_entity make_func_train() { return std::make_shared<Entity::Func::ATrain>(); }
	shared_ptr_entity make_func_water() { return std::make_shared<Entity::Func::AWater>(); }
	shared_ptr_entity make_func_conveyor() { return std::make_shared<Entity::Func::AConveyor>(); }
	shared_ptr_entity make_func_areaportal() { return std::make_shared<Entity::Func::AAreaportal>(); }
	shared_ptr_entity make_func_clock() { return std::make_shared<Entity::Func::AClock>(); }
	shared_ptr_entity make_func_wall() { return std::make_shared<Entity::Func::AWall>(); }
	shared_ptr_entity make_func_object() { return std::make_shared<Entity::Func::AObject>(); }
	shared_ptr_entity make_func_timer() { return std::make_shared<Entity::Func::ATimer>(); }
	shared_ptr_entity make_func_explosive() { return std::make_shared<Entity::Func::AExplosive>(); }
	shared_ptr_entity make_func_killbox() { return std::make_shared<Entity::Func::AKillbox>(); }
	shared_ptr_entity make_func_object_repair() { return std::make_shared<Entity::Func::AObjectRepair>(); }
	shared_ptr_entity make_rotating_light() { return std::make_shared<Entity::Rotating::ALight>(); }
	shared_ptr_entity make_trigger_always() { return std::make_shared<Entity::Trigger::AAlways>(); }
	shared_ptr_entity make_trigger_once() { return std::make_shared<Entity::Trigger::AOnce>(); }
	shared_ptr_entity make_trigger_multiple() { return std::make_shared<Entity::Trigger::AMultiple>(); }
	shared_ptr_entity make_trigger_relay() { return std::make_shared<Entity::Trigger::ARelay>(); }
	shared_ptr_entity make_trigger_push() { return std::make_shared<Entity::Trigger::APush>(); }
	shared_ptr_entity make_trigger_hurt() { return std::make_shared<Entity::Trigger::AHurt>(); }
	shared_ptr_entity make_trigger_key() { return std::make_shared<Entity::Trigger::AKey>(); }
	shared_ptr_entity make_trigger_counter() { return std::make_shared<Entity::Trigger::ACounter>(); }
	shared_ptr_entity make_trigger_elevator() { return std::make_shared<Entity::Trigger::AElevator>(); }
	shared_ptr_entity make_trigger_gravity() { return std::make_shared<Entity::Trigger::AGravity>(); }
	shared_ptr_entity make_trigger_monsterjump() { return std::make_shared<Entity::Trigger::AMonsterjump>(); }
	shared_ptr_entity make_target_temp_entity() { return std::make_shared<Entity::Target::ATempEntity>(); }
	shared_ptr_entity make_target_speaker() { return std::make_shared<Entity::Target::ASpeaker>(); }
	shared_ptr_entity make_target_explosion() { return std::make_shared<Entity::Target::AExplosion>(); }
	shared_ptr_entity make_target_changelevel() { return std::make_shared<Entity::Target::AChangelevel>(); }
	shared_ptr_entity make_target_secret() { return std::make_shared<Entity::Target::ASecret>(); }
	shared_ptr_entity make_target_goal() { return std::make_shared<Entity::Target::AGoal>(); }
	shared_ptr_entity make_target_splash() { return std::make_shared<Entity::Target::ASplash>(); }
	shared_ptr_entity make_target_spawner() { return std::make_shared<Entity::Target::ASpawner>(); }
	shared_ptr_entity make_target_blaster() { return std::make_shared<Entity::Target::ABlaster>(); }
	shared_ptr_entity make_target_crosslevel_trigger() { return std::make_shared<Entity::Target::ACrosslevelTrigger>(); }
	shared_ptr_entity make_target_crosslevel_target() { return std::make_shared<Entity::Target::ACrosslevelTarget>(); }
	shared_ptr_entity make_target_laser() { return std::make_shared<Entity::Target::ALaser>(); }
	shared_ptr_entity make_target_lightramp() { return std::make_shared<Entity::Target::ALightramp>(); }
	shared_ptr_entity make_target_earthquake() { return std::make_shared<Entity::Target::AEarthquake>(); }
	shared_ptr_entity make_target_character() { return std::make_shared<Entity::Target::ACharacter>(); }
	shared_ptr_entity make_target_string() { return std::make_shared<Entity::Target::AString>(); }
	shared_ptr_entity make_target_mal_laser() { return std::make_shared<Entity::Target::AMalLaser>(); }
	shared_ptr_entity make_worldspawn() { return std::make_shared<Entity::AWorldspawn>(); }
	shared_ptr_entity make_viewthing() { return std::make_shared<Entity::AViewthing>(); }
	shared_ptr_entity make_light() { return std::make_shared<Entity::ALight>(); }
	shared_ptr_entity make_light_mine1() { return std::make_shared<Entity::Light::AMine1>(); }
	shared_ptr_entity make_light_mine2() { return std::make_shared<Entity::Light::AMine2>(); }
	shared_ptr_entity make_info_null() { return std::make_shared<Entity::Info::ANull>(); }
	shared_ptr_entity make_func_group() { return std::make_shared<Entity::Func::AGroup>(); }
	shared_ptr_entity make_info_notnull() { return std::make_shared<Entity::Info::ANotnull>(); }
	shared_ptr_entity make_path_corner() { return std::make_shared<Entity::Path::ACorner>(); }
	shared_ptr_entity make_junior() { return std::make_shared<Entity::AJunior>(); }
	shared_ptr_entity make_misc_explobox() { return std::make_shared<Entity::Misc::AExplobox>(); }
	shared_ptr_entity make_misc_gib_arm() { return std::make_shared<Entity::Misc::AGibArm>(); }
	shared_ptr_entity make_misc_gib_leg() { return std::make_shared<Entity::Misc::AGibLeg>(); }
	shared_ptr_entity make_misc_gib_head() { return std::make_shared<Entity::Misc::AGibHead>(); }
	shared_ptr_entity make_misc_teleporter() { return std::make_shared<Entity::Misc::ATeleporter>(); }
	shared_ptr_entity make_misc_teleporter_dest() { return std::make_shared<Entity::Misc::ATeleporterDest>(); }
	shared_ptr_entity make_misc_amb4() { return std::make_shared<Entity::Misc::AAmb4>(); }
	shared_ptr_entity make_cast_punk() { return std::make_shared<Entity::Cast::APunk>(); }
	shared_ptr_entity make_cast_thug() { return std::make_shared<Entity::Cast::AThug>(); }
	shared_ptr_entity make_cast_thug_sit() { return std::make_shared<Entity::Cast::AThugSit>(); }
	shared_ptr_entity make_cast_bitch() { return std::make_shared<Entity::Cast::ABitch>(); }
	shared_ptr_entity make_cast_dog() { return std::make_shared<Entity::Cast::ADog>(); }
	shared_ptr_entity make_cast_runt() { return std::make_shared<Entity::Cast::ARunt>(); }
	shared_ptr_entity make_cast_bum_sit() { return std::make_shared<Entity::Cast::ABumSit>(); }
	shared_ptr_entity make_cast_shorty() { return std::make_shared<Entity::Cast::AShorty>(); }
	shared_ptr_entity make_cast_whore() { return std::make_shared<Entity::Cast::AWhore>(); }
	shared_ptr_entity make_cast_punk_window() { return std::make_shared<Entity::Cast::APunkWindow>(); }
	shared_ptr_entity make_cast_punk2() { return std::make_shared<Entity::Cast::APunk2>(); }
	shared_ptr_entity make_cast_rosie() { return std::make_shared<Entity::Cast::ARosie>(); }
	shared_ptr_entity make_ai_boundary() { return std::make_shared<Entity::Ai::ABoundary>(); }
	shared_ptr_entity make_ai_event_hostile() { return std::make_shared<Entity::Ai::AEventHostile>(); }
	shared_ptr_entity make_ai_event_follow() { return std::make_shared<Entity::Ai::AEventFollow>(); }
	shared_ptr_entity make_ai_guard() { return std::make_shared<Entity::Ai::AGuard>(); }
	shared_ptr_entity make_ai_territory() { return std::make_shared<Entity::Ai::ATerritory>(); }
	shared_ptr_entity make_ai_trigger_character() { return std::make_shared<Entity::Ai::ATriggerCharacter>(); }
	shared_ptr_entity make_ai_locked_door() { return std::make_shared<Entity::Ai::ALockedDoor>(); }
	shared_ptr_entity make_misc_skidrow_radio() { return std::make_shared<Entity::Misc::ASkidrowRadio>(); }
	shared_ptr_entity make_misc_skidrow_ambush() { return std::make_shared<Entity::Misc::ASkidrowAmbush>(); }
	shared_ptr_entity make_misc_skidrow_radio_repeater() { return std::make_shared<Entity::Misc::ASkidrowRadioRepeater>(); }shared_ptr_entity make_ai_ty_fuseblown() { return std::make_shared<Entity::Ai::ATyFuseblown>(); }
	shared_ptr_entity make_ai_moker_notinoffice() { return std::make_shared<Entity::Ai::AMokerNotinoffice>(); }
	shared_ptr_entity make_misc_grunt() { return std::make_shared<Entity::Misc::AGrunt>(); }
	shared_ptr_entity make_misc_fidelA() { return std::make_shared<Entity::Misc::AFidela>(); }
	shared_ptr_entity make_misc_car() { return std::make_shared<Entity::Misc::ACar>(); }
	shared_ptr_entity make_misc_smoke() { return std::make_shared<Entity::Misc::ASmoke>(); }
	shared_ptr_entity make_elps() { return std::make_shared<Entity::AElps>(); }
	shared_ptr_entity make_misc_alarm() { return std::make_shared<Entity::Misc::AAlarm>(); }
	shared_ptr_entity make_trigger_hurt_electric() { return std::make_shared<Entity::Trigger::AHurtElectric>(); }
	shared_ptr_entity make_pawn_o_matic() { return std::make_shared<Entity::Pawn::AOMatic>(); }
	shared_ptr_entity make_ai_safespot() { return std::make_shared<Entity::Ai::ASafespot>(); }
	shared_ptr_entity make_misc_skidrow_ai_reset() { return std::make_shared<Entity::Misc::ASkidrowAiReset>(); }
	shared_ptr_entity make_ai_combat_spot() { return std::make_shared<Entity::Ai::ACombatSpot>(); }
	shared_ptr_entity make_misc_skidrow_afraid() { return std::make_shared<Entity::Misc::ASkidrowAfraid>(); }
	shared_ptr_entity make_misc_steeltown_afraid() { return std::make_shared<Entity::Misc::ASteeltownAfraid>(); }
	shared_ptr_entity make_misc_kroker_afraid() { return std::make_shared<Entity::Misc::AKrokerAfraid>(); }
	shared_ptr_entity make_rc_initiation_observer() { return std::make_shared<Entity::Rc::AInitiationObserver>(); }
	shared_ptr_entity make_rc_initiation_brush() { return std::make_shared<Entity::Rc::AInitiationBrush>(); }
	shared_ptr_entity make_misc_pv_afraid() { return std::make_shared<Entity::Misc::APvAfraid>(); }
	shared_ptr_entity make_misc_ty_afraid() { return std::make_shared<Entity::Misc::ATyAfraid>(); }
	shared_ptr_entity make_ai_ty_mo_boundry() { return std::make_shared<Entity::Ai::ATyMoBoundry>(); }
	shared_ptr_entity make_ai_sy_dykes_boundry() { return std::make_shared<Entity::Ai::ASyDykesBoundry>(); }
	shared_ptr_entity make_misc_sy_afraid() { return std::make_shared<Entity::Misc::ASyAfraid>(); }
	shared_ptr_entity make_ep_skidrow_flag() { return std::make_shared<Entity::Ep::ASkidrowFlag>(); }
	shared_ptr_entity make_ai_sy_oilcan() { return std::make_shared<Entity::Ai::ASyOilcan>(); }
	shared_ptr_entity make_ai_ty_valvehandle() { return std::make_shared<Entity::Ai::ATyValvehandle>(); }
	shared_ptr_entity make_ai_pv_fuseblown1() { return std::make_shared<Entity::Ai::APvFuseblown1>(); }
	shared_ptr_entity make_ai_pv_fuseblown2() { return std::make_shared<Entity::Ai::APvFuseblown2>(); }
	shared_ptr_entity make_ai_pv_deadlouie() { return std::make_shared<Entity::Ai::APvDeadlouie>(); }
	shared_ptr_entity make_ai_sy_blefty() { return std::make_shared<Entity::Ai::ASyBlefty>(); }
	shared_ptr_entity make_misc_barry_bitch() { return std::make_shared<Entity::Misc::ABarryBitch>(); }
	shared_ptr_entity make_misc_corky_fidel_mdx_pcx() { return std::make_shared<Entity::Misc::ACorkyFidelMdxPcx>(); }
	shared_ptr_entity make_misc_corky_fidel_mdx_tga() { return std::make_shared<Entity::Misc::ACorkyFidelMdxTga>(); }
	shared_ptr_entity make_misc_cut_scene() { return std::make_shared<Entity::Misc::ACutScene>(); }
	shared_ptr_entity make_light_fire_esm() { return std::make_shared<Entity::Light::AFireEsm>(); }
	shared_ptr_entity make_light_fire_sm() { return std::make_shared<Entity::Light::AFireSm>(); }
	shared_ptr_entity make_light_fire_med() { return std::make_shared<Entity::Light::AFireMed>(); }
	shared_ptr_entity make_light_fire_lg() { return std::make_shared<Entity::Light::AFireLg>(); }
	shared_ptr_entity make_smoke_esm() { return std::make_shared<Entity::Smoke::AEsm>(); }
	shared_ptr_entity make_smoke_sm() { return std::make_shared<Entity::Smoke::ASm>(); }
	shared_ptr_entity make_smoke_med() { return std::make_shared<Entity::Smoke::AMed>(); }
	shared_ptr_entity make_smoke_lg() { return std::make_shared<Entity::Smoke::ALg>(); }
	shared_ptr_entity make_func_train_rotating() { return std::make_shared<Entity::Func::ATrainRotating>(); }
	shared_ptr_entity make_func_subdoor_base() { return std::make_shared<Entity::Func::ASubdoorBase>(); }
	shared_ptr_entity make_func_subdoor_handle1() { return std::make_shared<Entity::Func::ASubdoorHandle1>(); }
	shared_ptr_entity make_func_subdoor_handle2() { return std::make_shared<Entity::Func::ASubdoorHandle2>(); }
	shared_ptr_entity make_props_trashcanA() { return std::make_shared<Entity::Props::ATrashcana>(); }
	shared_ptr_entity make_props_trashcan_fall() { return std::make_shared<Entity::Props::ATrashcanFall>(); }
	shared_ptr_entity make_props_hydrant() { return std::make_shared<Entity::Props::AHydrant>(); }
	shared_ptr_entity make_props_antenna1a() { return std::make_shared<Entity::Props::AAntenna1a>(); }
	shared_ptr_entity make_props_antenna1b() { return std::make_shared<Entity::Props::AAntenna1b>(); }
	shared_ptr_entity make_props_antenna1c() { return std::make_shared<Entity::Props::AAntenna1c>(); }
	shared_ptr_entity make_props_antenna2a() { return std::make_shared<Entity::Props::AAntenna2a>(); }
	shared_ptr_entity make_props_antenna2b() { return std::make_shared<Entity::Props::AAntenna2b>(); }
	shared_ptr_entity make_props_antenna2c() { return std::make_shared<Entity::Props::AAntenna2c>(); }
	shared_ptr_entity make_props_antenna3a() { return std::make_shared<Entity::Props::AAntenna3a>(); }
	shared_ptr_entity make_props_antenna3b() { return std::make_shared<Entity::Props::AAntenna3b>(); }
	shared_ptr_entity make_props_antenna3c() { return std::make_shared<Entity::Props::AAntenna3c>(); }
	shared_ptr_entity make_props_fan() { return std::make_shared<Entity::Props::AFan>(); }
	shared_ptr_entity make_props_phone() { return std::make_shared<Entity::Props::APhone>(); }
	shared_ptr_entity make_props_aircon() { return std::make_shared<Entity::Props::AAircon>(); }
	shared_ptr_entity make_props_tablesetA() { return std::make_shared<Entity::Props::ATableseta>(); }
	shared_ptr_entity make_props_radio() { return std::make_shared<Entity::Props::ARadio>(); }
	shared_ptr_entity make_cast_buma() { return std::make_shared<Entity::Cast::ABuma>(); }
	shared_ptr_entity make_cast_bumb() { return std::make_shared<Entity::Cast::ABumb>(); }
	shared_ptr_entity make_elements_raincloud() { return std::make_shared<Entity::Elements::ARaincloud>(); }
	shared_ptr_entity make_elements_snowcloud() { return std::make_shared<Entity::Elements::ASnowcloud>(); }
	shared_ptr_entity make_misc_cutscene_trigger() { return std::make_shared<Entity::Misc::ACutsceneTrigger>(); }
	shared_ptr_entity make_misc_cutscene_camera() { return std::make_shared<Entity::Misc::ACutsceneCamera>(); }
	shared_ptr_entity make_trigger_unlock() { return std::make_shared<Entity::Trigger::AUnlock>(); }
	shared_ptr_entity make_props_chair() { return std::make_shared<Entity::Props::AChair>(); }
	shared_ptr_entity make_props_extinguisherA() { return std::make_shared<Entity::Props::AExtinguishera>(); }
	shared_ptr_entity make_props_extinguisherB() { return std::make_shared<Entity::Props::AExtinguisherb>(); }
	shared_ptr_entity make_light_sconce() { return std::make_shared<Entity::Light::ASconce>(); }
	shared_ptr_entity make_props_motorcycle() { return std::make_shared<Entity::Props::AMotorcycle>(); }
	shared_ptr_entity make_props_ammocrate_bust() { return std::make_shared<Entity::Props::AAmmocrateBust>(); }
	shared_ptr_entity make_props_shelf() { return std::make_shared<Entity::Props::AShelf>(); }
	shared_ptr_entity make_props_mattressA() { return std::make_shared<Entity::Props::AMattressa>(); }
	shared_ptr_entity make_props_mattressB() { return std::make_shared<Entity::Props::AMattressb>(); }
	shared_ptr_entity make_props_mattressC() { return std::make_shared<Entity::Props::AMattressc>(); }
	shared_ptr_entity make_trigger_motorcycle() { return std::make_shared<Entity::Trigger::AMotorcycle>(); }
	shared_ptr_entity make_props_tv() { return std::make_shared<Entity::Props::ATv>(); }
	shared_ptr_entity make_props_steam_machine() { return std::make_shared<Entity::Props::ASteamMachine>(); }
	shared_ptr_entity make_light_bulb() { return std::make_shared<Entity::Light::ABulb>(); }
	shared_ptr_entity make_props_trash() { return std::make_shared<Entity::Props::ATrash>(); }
	shared_ptr_entity make_props_wall_fall() { return std::make_shared<Entity::Props::AWallFall>(); }
	shared_ptr_entity make_props_trashbottle() { return std::make_shared<Entity::Props::ATrashbottle>(); }
	shared_ptr_entity make_props_trashwall() { return std::make_shared<Entity::Props::ATrashwall>(); }
	shared_ptr_entity make_props_trashpaper() { return std::make_shared<Entity::Props::ATrashpaper>(); }
	shared_ptr_entity make_props_trashcorner() { return std::make_shared<Entity::Props::ATrashcorner>(); }
	shared_ptr_entity make_props_trashbottle_vert() { return std::make_shared<Entity::Props::ATrashbottleVert>(); }
	shared_ptr_entity make_props_blimp() { return std::make_shared<Entity::Props::ABlimp>(); }
	shared_ptr_entity make_misc_use_cutscene() { return std::make_shared<Entity::Misc::AUseCutscene>(); }
	shared_ptr_entity make_props_motorcycle_runaway() { return std::make_shared<Entity::Props::AMotorcycleRunaway>(); }
	shared_ptr_entity make_trigger_hurt_fire() { return std::make_shared<Entity::Trigger::AHurtFire>(); }
	shared_ptr_entity make_props_shelf_fall() { return std::make_shared<Entity::Props::AShelfFall>(); }
	shared_ptr_entity make_target_fire() { return std::make_shared<Entity::Target::AFire>(); }
	shared_ptr_entity make_props_rat() { return std::make_shared<Entity::Props::ARat>(); }
	shared_ptr_entity make_props_rat_spawner() { return std::make_shared<Entity::Props::ARatSpawner>(); }
	shared_ptr_entity make_props_rat_spawner_node() { return std::make_shared<Entity::Props::ARatSpawnerNode>(); }
	shared_ptr_entity make_target_flamethrower() { return std::make_shared<Entity::Target::AFlamethrower>(); }
	shared_ptr_entity make_light_deco_sconce() { return std::make_shared<Entity::Light::ADecoSconce>(); }
	shared_ptr_entity make_light_pendant() { return std::make_shared<Entity::Light::APendant>(); }
	shared_ptr_entity make_props_shelfB_fall() { return std::make_shared<Entity::Props::AShelfbFall>(); }
	shared_ptr_entity make_func_lift() { return std::make_shared<Entity::Func::ALift>(); }
	shared_ptr_entity make_props_roof_vent() { return std::make_shared<Entity::Props::ARoofVent>(); }
	shared_ptr_entity make_props_rat_trigger() { return std::make_shared<Entity::Props::ARatTrigger>(); }
	shared_ptr_entity make_props2_truck_die() { return std::make_shared<Entity::Props2::ATruckDie>(); }
	shared_ptr_entity make_props_cola_machine() { return std::make_shared<Entity::Props::AColaMachine>(); }
	shared_ptr_entity make_props_cig_machine() { return std::make_shared<Entity::Props::ACigMachine>(); }
	shared_ptr_entity make_props2_barrels_fallA() { return std::make_shared<Entity::Props2::ABarrelsFalla>(); }
	shared_ptr_entity make_props2_barrels_fallB() { return std::make_shared<Entity::Props2::ABarrelsFallb>(); }
	shared_ptr_entity make_props2_clubcouch() { return std::make_shared<Entity::Props2::AClubcouch>(); }
	shared_ptr_entity make_props2_clubchair() { return std::make_shared<Entity::Props2::AClubchair>(); }
	shared_ptr_entity make_props2_vaseA() { return std::make_shared<Entity::Props2::AVasea>(); }
	shared_ptr_entity make_props2_vaseB() { return std::make_shared<Entity::Props2::AVaseb>(); }
	shared_ptr_entity make_props2_chair_conf() { return std::make_shared<Entity::Props2::AChairConf>(); }
	shared_ptr_entity make_props2_shelf_metal_A_fall() { return std::make_shared<Entity::Props2::AShelfMetalAFall>(); }
	shared_ptr_entity make_props2_shelf_metal_B_fall() { return std::make_shared<Entity::Props2::AShelfMetalBFall>(); }
	shared_ptr_entity make_props2_deadguy() { return std::make_shared<Entity::Props2::ADeadguy>(); }
	shared_ptr_entity make_props2_chair_push() { return std::make_shared<Entity::Props2::AChairPush>(); }
	shared_ptr_entity make_props_crate_bust_32() { return std::make_shared<Entity::Props::ACrateBust32>(); }
	shared_ptr_entity make_props_crate_bust_48() { return std::make_shared<Entity::Props::ACrateBust48>(); }
	shared_ptr_entity make_props_crate_bust_64() { return std::make_shared<Entity::Props::ACrateBust64>(); }
	shared_ptr_entity make_props2_flag() { return std::make_shared<Entity::Props2::AFlag>(); }
	shared_ptr_entity make_props2_fish() { return std::make_shared<Entity::Props2::AFish>(); }
	shared_ptr_entity make_props2_fish_trigger() { return std::make_shared<Entity::Props2::AFishTrigger>(); }
	shared_ptr_entity make_props2_fish_spawner() { return std::make_shared<Entity::Props2::AFishSpawner>(); }
	shared_ptr_entity make_props2_fish_spawner_node() { return std::make_shared<Entity::Props2::AFishSpawnerNode>(); }
	shared_ptr_entity make_props2_wall_fish() { return std::make_shared<Entity::Props2::AWallFish>(); }
	shared_ptr_entity make_props2_barrels_fall_ST() { return std::make_shared<Entity::Props2::ABarrelsFallSt>(); }
	shared_ptr_entity make_props2_sign() { return std::make_shared<Entity::Props2::ASign>(); }
	shared_ptr_entity make_props2_lighthouse_beam() { return std::make_shared<Entity::Props2::ALighthouseBeam>(); }
	shared_ptr_entity make_props2_boat() { return std::make_shared<Entity::Props2::ABoat>(); }
	shared_ptr_entity make_props2_buoy() { return std::make_shared<Entity::Props2::ABuoy>(); }
	shared_ptr_entity make_props2_buoy_side() { return std::make_shared<Entity::Props2::ABuoySide>(); }
	shared_ptr_entity make_props2_deadguy_underwater() { return std::make_shared<Entity::Props2::ADeadguyUnderwater>(); }
	shared_ptr_entity make_props2_buoy_animate() { return std::make_shared<Entity::Props2::ABuoyAnimate>(); }
	shared_ptr_entity make_props2_gargoyle() { return std::make_shared<Entity::Props2::AGargoyle>(); }
	shared_ptr_entity make_props2_clothesline() { return std::make_shared<Entity::Props2::AClothesline>(); }
	shared_ptr_entity make_props2_plant_XL() { return std::make_shared<Entity::Props2::APlantXl>(); }
	shared_ptr_entity make_props2_plant_SM() { return std::make_shared<Entity::Props2::APlantSm>(); }
	shared_ptr_entity make_props2_boatphone() { return std::make_shared<Entity::Props2::ABoatphone>(); }
	shared_ptr_entity make_props2_ashtray() { return std::make_shared<Entity::Props2::AAshtray>(); }
	shared_ptr_entity make_props2_lunch() { return std::make_shared<Entity::Props2::ALunch>(); }
	shared_ptr_entity make_props2_deadgal_headless() { return std::make_shared<Entity::Props2::ADeadgalHeadless>(); }
	shared_ptr_entity make_props2_plant_bush() { return std::make_shared<Entity::Props2::APlantBush>(); }
	shared_ptr_entity make_props2_boat_animate() { return std::make_shared<Entity::Props2::ABoatAnimate>(); }
	shared_ptr_entity make_props2_helicopter_animate() { return std::make_shared<Entity::Props2::AHelicopterAnimate>(); }
	shared_ptr_entity make_props2_car_animate() { return std::make_shared<Entity::Props2::ACarAnimate>(); }
	shared_ptr_entity make_props2_car_topdown() { return std::make_shared<Entity::Props2::ACarTopdown>(); }
	shared_ptr_entity make_props2_car_topup() { return std::make_shared<Entity::Props2::ACarTopup>(); }
	shared_ptr_entity make_props2_plant_fern() { return std::make_shared<Entity::Props2::APlantFern>(); }
	shared_ptr_entity make_props2_pinball_machine() { return std::make_shared<Entity::Props2::APinballMachine>(); }
	shared_ptr_entity make_props2_barrels_PV_A() { return std::make_shared<Entity::Props2::ABarrelsPvA>(); }
	shared_ptr_entity make_props2_barrels_PV_C() { return std::make_shared<Entity::Props2::ABarrelsPvC>(); }
	shared_ptr_entity make_props2_barrels_PV_D() { return std::make_shared<Entity::Props2::ABarrelsPvD>(); }
	shared_ptr_entity make_props2_barrels_PV_E() { return std::make_shared<Entity::Props2::ABarrelsPvE>(); }
	shared_ptr_entity make_props2_barrels_PV_F() { return std::make_shared<Entity::Props2::ABarrelsPvF>(); }
	shared_ptr_entity make_light_chandelier() { return std::make_shared<Entity::Light::AChandelier>(); }
	shared_ptr_entity make_props2_air_train() { return std::make_shared<Entity::Props2::AAirTrain>(); }
	shared_ptr_entity make_props3_dead_louie() { return std::make_shared<Entity::Props3::ADeadLouie>(); }
	shared_ptr_entity make_props3_cut_boss_player_animate() { return std::make_shared<Entity::Props3::ACutBossPlayerAnimate>(); }
	shared_ptr_entity make_props3_deco_fixture() { return std::make_shared<Entity::Props3::ADecoFixture>(); }
	shared_ptr_entity make_props3_cut_boss_chick_animate() { return std::make_shared<Entity::Props3::ACutBossChickAnimate>(); }
	shared_ptr_entity make_props3_cut_train_run_animate() { return std::make_shared<Entity::Props3::ACutTrainRunAnimate>(); }
	shared_ptr_entity make_props3_cut_A_animate() { return std::make_shared<Entity::Props3::ACutAAnimate>(); }
	shared_ptr_entity make_props3_cut_B_animate() { return std::make_shared<Entity::Props3::ACutBAnimate>(); }
	shared_ptr_entity make_props3_cut_C_animate() { return std::make_shared<Entity::Props3::ACutCAnimate>(); }
	shared_ptr_entity make_props3_cut_D_animate() { return std::make_shared<Entity::Props3::ACutDAnimate>(); }
	shared_ptr_entity make_props3_cash_counter_animate() { return std::make_shared<Entity::Props3::ACashCounterAnimate>(); }shared_ptr_entity make_props2_barrels_PV_B() { return std::make_shared<Entity::Props2::ABarrelsPvB>(); }
	shared_ptr_entity make_props3_decanter() { return std::make_shared<Entity::Props3::ADecanter>(); }
	shared_ptr_entity make_props3_whiskey_glass() { return std::make_shared<Entity::Props3::AWhiskeyGlass>(); }
	shared_ptr_entity make_props3_barrels_fall_nikki_A() { return std::make_shared<Entity::Props3::ABarrelsFallNikkiA>(); }
	shared_ptr_entity make_props3_barrels_fall_nikki_B() { return std::make_shared<Entity::Props3::ABarrelsFallNikkiB>(); }
	shared_ptr_entity make_props3_cut_run_to_car_animate() { return std::make_shared<Entity::Props3::ACutRunToCarAnimate>(); }
	shared_ptr_entity make_props3_cut_final_animate() { return std::make_shared<Entity::Props3::ACutFinalAnimate>(); }
	shared_ptr_entity make_props3_cash() { return std::make_shared<Entity::Props3::ACash>(); }
	shared_ptr_entity make_props3_cut_truck_driver() { return std::make_shared<Entity::Props3::ACutTruckDriver>(); }
	shared_ptr_entity make_props3_cut_pinball_guy_animate() { return std::make_shared<Entity::Props3::ACutPinballGuyAnimate>(); }
	shared_ptr_entity make_lightflare() { return std::make_shared<Entity::ALightflare>(); }
	shared_ptr_entity make_path_corner_cast() { return std::make_shared<Entity::Path::ACornerCast>(); }
	shared_ptr_entity make_pistol_mod_damage() { return std::make_shared<Entity::Pistol::AModDamage>(); }
	shared_ptr_entity make_pistol_mod_rof() { return std::make_shared<Entity::Pistol::AModRof>(); }
	shared_ptr_entity make_pistol_mod_reload() { return std::make_shared<Entity::Pistol::AModReload>(); }
	shared_ptr_entity make_hmg_mod_cooling() { return std::make_shared<Entity::Hmg::AModCooling>(); }
	shared_ptr_entity make_sfx_beacon() { return std::make_shared<Entity::Sfx::ABeacon>(); }
	shared_ptr_entity make_refl() { return std::make_shared<Entity::ARefl>(); }
	shared_ptr_entity make_dm_cashspawn() { return std::make_shared<Entity::Dm::ACashspawn>(); }
	shared_ptr_entity make_dm_safebag() { return std::make_shared<Entity::Dm::ASafebag>(); }
	shared_ptr_entity make_dm_props_banner() { return std::make_shared<Entity::Dm::APropsBanner>(); }

	static const std::unordered_map<std::string_view, shared_ptr_entity(*)()> classes =
	{
		{ "item_health", make_item_health },
		{ "item_health_small", make_item_health_small },
		{ "item_health_large", make_item_health_large },
		{ "item_health_mega", make_item_health_mega },
		{ "info_player_start", make_info_player_start },
		{ "info_player_deathmatch", make_info_player_deathmatch },
		{ "info_player_coop", make_info_player_coop },
		{ "info_player_intermission", make_info_player_intermission },
		{ "func_plat", make_func_plat },
		{ "func_button", make_func_button },
		{ "func_door", make_func_door },
		{ "func_door_secret", make_func_door_secret },
		{ "func_door_rotating", make_func_door_rotating },
		{ "func_rotating", make_func_rotating },
		{ "func_train", make_func_train },
		{ "func_water", make_func_water },
		{ "func_conveyor", make_func_conveyor },
		{ "func_areaportal", make_func_areaportal },
		{ "func_clock", make_func_clock },
		{ "func_wall", make_func_wall },
		{ "func_object", make_func_object },
		{ "func_timer", make_func_timer },
		{ "func_explosive", make_func_explosive },
		{ "func_killbox", make_func_killbox },
		{ "func_object_repair", make_func_object_repair },
		{ "rotating_light", make_rotating_light },
		{ "trigger_always", make_trigger_always },
		{ "trigger_once", make_trigger_once },
		{ "trigger_multiple", make_trigger_multiple },
		{ "trigger_relay", make_trigger_relay },
		{ "trigger_push", make_trigger_push },
		{ "trigger_hurt", make_trigger_hurt },
		{ "trigger_key", make_trigger_key },
		{ "trigger_counter", make_trigger_counter },
		{ "trigger_elevator", make_trigger_elevator },
		{ "trigger_gravity", make_trigger_gravity },
		{ "trigger_monsterjump", make_trigger_monsterjump },
		{ "target_temp_entity", make_target_temp_entity },
		{ "target_speaker", make_target_speaker },
		{ "target_explosion", make_target_explosion },
		{ "target_changelevel", make_target_changelevel },
		{ "target_secret", make_target_secret },
		{ "target_goal", make_target_goal },
		{ "target_splash", make_target_splash },
		{ "target_spawner", make_target_spawner },
		{ "target_blaster", make_target_blaster },
		{ "target_crosslevel_trigger", make_target_crosslevel_trigger },
		{ "target_crosslevel_target", make_target_crosslevel_target },
		{ "target_laser", make_target_laser },
		{ "target_lightramp", make_target_lightramp },
		{ "target_earthquake", make_target_earthquake },
		{ "target_character", make_target_character },
		{ "target_string", make_target_string },
		{ "target_mal_laser", make_target_mal_laser },
		{ "worldspawn", make_worldspawn },
		{ "viewthing", make_viewthing },
		{ "light", make_light },
		{ "light_mine1", make_light_mine1 },
		{ "light_mine2", make_light_mine2 },
		{ "info_null", make_info_null },
		{ "func_group", make_func_group },
		{ "info_notnull", make_info_notnull },
		{ "path_corner", make_path_corner },
		{ "junior", make_junior },
		{ "misc_explobox", make_misc_explobox },
		{ "misc_gib_arm", make_misc_gib_arm },
		{ "misc_gib_leg", make_misc_gib_leg },
		{ "misc_gib_head", make_misc_gib_head },
		{ "misc_teleporter", make_misc_teleporter },
		{ "misc_teleporter_dest", make_misc_teleporter_dest },
		{ "misc_amb4", make_misc_amb4 },
		{ "cast_punk", make_cast_punk },
		{ "cast_thug", make_cast_thug },
		{ "cast_thug_sit", make_cast_thug_sit },
		{ "cast_bitch", make_cast_bitch },
		{ "cast_dog", make_cast_dog },
		{ "cast_runt", make_cast_runt },
		{ "cast_bum_sit", make_cast_bum_sit },
		{ "cast_shorty", make_cast_shorty },
		{ "cast_whore", make_cast_whore },
		{ "cast_punk_window", make_cast_punk_window },
		{ "cast_punk2", make_cast_punk2 },
		{ "cast_rosie", make_cast_rosie },
		{ "ai_boundary", make_ai_boundary },
		{ "ai_event_hostile", make_ai_event_hostile },
		{ "ai_event_follow", make_ai_event_follow },
		{ "ai_guard", make_ai_guard },
		{ "ai_territory", make_ai_territory },
		{ "ai_trigger_character", make_ai_trigger_character },
		{ "ai_locked_door", make_ai_locked_door },
		{ "misc_skidrow_radio", make_misc_skidrow_radio },
		{ "misc_skidrow_ambush", make_misc_skidrow_ambush },
		{ "misc_skidrow_radio_repeater", make_misc_skidrow_radio_repeater },
		{ "ai_ty_fuseblown", make_ai_ty_fuseblown },
		{ "ai_moker_notinoffice", make_ai_moker_notinoffice },
		{ "misc_grunt", make_misc_grunt },
		{ "misc_fidelA", make_misc_fidelA },
		{ "misc_car", make_misc_car },
		{ "misc_smoke", make_misc_smoke },
		{ "elps", make_elps },
		{ "misc_alarm", make_misc_alarm },
		{ "trigger_hurt_electric", make_trigger_hurt_electric },
		{ "pawn_o_matic", make_pawn_o_matic },
		{ "ai_safespot", make_ai_safespot },
		{ "misc_skidrow_ai_reset", make_misc_skidrow_ai_reset },
		{ "ai_combat_spot", make_ai_combat_spot },
		{ "misc_skidrow_afraid", make_misc_skidrow_afraid },
		{ "misc_steeltown_afraid", make_misc_steeltown_afraid },
		{ "misc_kroker_afraid", make_misc_kroker_afraid },
		{ "rc_initiation_observer", make_rc_initiation_observer },
		{ "rc_initiation_brush", make_rc_initiation_brush },
		{ "misc_pv_afraid", make_misc_pv_afraid },
		{ "misc_ty_afraid", make_misc_ty_afraid },
		{ "ai_ty_mo_boundry", make_ai_ty_mo_boundry },
		{ "ai_sy_dykes_boundry", make_ai_sy_dykes_boundry },
		{ "misc_sy_afraid", make_misc_sy_afraid },
		{ "ep_skidrow_flag", make_ep_skidrow_flag },
		{ "ai_sy_oilcan", make_ai_sy_oilcan },
		{ "ai_ty_valvehandle", make_ai_ty_valvehandle },
		{ "ai_pv_fuseblown1", make_ai_pv_fuseblown1 },
		{ "ai_pv_fuseblown2", make_ai_pv_fuseblown2 },
		{ "ai_pv_deadlouie", make_ai_pv_deadlouie },
		{ "ai_sy_blefty", make_ai_sy_blefty },
		{ "misc_barry_bitch", make_misc_barry_bitch },
		{ "misc_corky_fidel_mdx_pcx", make_misc_corky_fidel_mdx_pcx },
		{ "misc_corky_fidel_mdx_tga", make_misc_corky_fidel_mdx_tga },
		{ "misc_cut_scene", make_misc_cut_scene },
		{ "light_fire_esm", make_light_fire_esm },
		{ "light_fire_sm", make_light_fire_sm },
		{ "light_fire_med", make_light_fire_med },
		{ "light_fire_lg", make_light_fire_lg },
		{ "smoke_esm", make_smoke_esm },
		{ "smoke_sm", make_smoke_sm },
		{ "smoke_med", make_smoke_med },
		{ "smoke_lg", make_smoke_lg },
		{ "func_train_rotating", make_func_train_rotating },
		{ "func_subdoor_base", make_func_subdoor_base },
		{ "func_subdoor_handle1", make_func_subdoor_handle1 },
		{ "func_subdoor_handle2", make_func_subdoor_handle2 },
		{ "props_trashcanA", make_props_trashcanA },
		{ "props_trashcan_fall", make_props_trashcan_fall },
		{ "props_hydrant", make_props_hydrant },
		{ "props_antenna1a", make_props_antenna1a },
		{ "props_antenna1b", make_props_antenna1b },
		{ "props_antenna1c", make_props_antenna1c },
		{ "props_antenna2a", make_props_antenna2a },
		{ "props_antenna2b", make_props_antenna2b },
		{ "props_antenna2c", make_props_antenna2c },
		{ "props_antenna3a", make_props_antenna3a },
		{ "props_antenna3b", make_props_antenna3b },
		{ "props_antenna3c", make_props_antenna3c },
		{ "props_fan", make_props_fan },
		{ "props_phone", make_props_phone },
		{ "props_aircon", make_props_aircon },
		{ "props_tablesetA", make_props_tablesetA },
		{ "props_radio", make_props_radio },
		{ "cast_buma", make_cast_buma },
		{ "cast_bumb", make_cast_bumb },
		{ "elements_raincloud", make_elements_raincloud },
		{ "elements_snowcloud", make_elements_snowcloud },
		{ "misc_cutscene_trigger", make_misc_cutscene_trigger },
		{ "misc_cutscene_camera", make_misc_cutscene_camera },
		{ "trigger_unlock", make_trigger_unlock },
		{ "props_chair", make_props_chair },
		{ "props_extinguisherA", make_props_extinguisherA },
		{ "props_extinguisherB", make_props_extinguisherB },
		{ "light_sconce", make_light_sconce },
		{ "props_motorcycle", make_props_motorcycle },
		{ "props_ammocrate_bust", make_props_ammocrate_bust },
		{ "props_shelf", make_props_shelf },
		{ "props_mattressA", make_props_mattressA },
		{ "props_mattressB", make_props_mattressB },
		{ "props_mattressC", make_props_mattressC },
		{ "trigger_motorcycle", make_trigger_motorcycle },
		{ "props_tv", make_props_tv },
		{ "props_steam_machine", make_props_steam_machine },
		{ "light_bulb", make_light_bulb },
		{ "props_trash", make_props_trash },
		{ "props_wall_fall", make_props_wall_fall },
		{ "props_trashbottle", make_props_trashbottle },
		{ "props_trashwall", make_props_trashwall },
		{ "props_trashpaper", make_props_trashpaper },
		{ "props_trashcorner", make_props_trashcorner },
		{ "props_trashbottle_vert", make_props_trashbottle_vert },
		{ "props_blimp", make_props_blimp },
		{ "misc_use_cutscene", make_misc_use_cutscene },
		{ "props_motorcycle_runaway", make_props_motorcycle_runaway },
		{ "trigger_hurt_fire", make_trigger_hurt_fire },
		{ "props_shelf_fall", make_props_shelf_fall },
		{ "target_fire", make_target_fire },
		{ "props_rat", make_props_rat },
		{ "props_rat_spawner", make_props_rat_spawner },
		{ "props_rat_spawner_node", make_props_rat_spawner_node },
		{ "target_flamethrower", make_target_flamethrower },
		{ "light_deco_sconce", make_light_deco_sconce },
		{ "light_pendant", make_light_pendant },
		{ "props_shelfB_fall", make_props_shelfB_fall },
		{ "func_lift", make_func_lift },
		{ "props_roof_vent", make_props_roof_vent },
		{ "props_rat_trigger", make_props_rat_trigger },
		{ "props2_truck_die", make_props2_truck_die },
		{ "props_cola_machine", make_props_cola_machine },
		{ "props_cig_machine", make_props_cig_machine },
		{ "props2_barrels_fallA", make_props2_barrels_fallA },
		{ "props2_barrels_fallB", make_props2_barrels_fallB },
		{ "props2_clubcouch", make_props2_clubcouch },
		{ "props2_clubchair", make_props2_clubchair },
		{ "props2_vaseA", make_props2_vaseA },
		{ "props2_vaseB", make_props2_vaseB },
		{ "props2_chair_conf", make_props2_chair_conf },
		{ "props2_shelf_metal_A_fall", make_props2_shelf_metal_A_fall },
		{ "props2_shelf_metal_B_fall", make_props2_shelf_metal_B_fall },
		{ "props2_deadguy", make_props2_deadguy },
		{ "props2_chair_push", make_props2_chair_push },
		{ "props_crate_bust_32", make_props_crate_bust_32 },
		{ "props_crate_bust_48", make_props_crate_bust_48 },
		{ "props_crate_bust_64", make_props_crate_bust_64 },
		{ "props2_flag", make_props2_flag },
		{ "props2_fish", make_props2_fish },
		{ "props2_fish_trigger", make_props2_fish_trigger },
		{ "props2_fish_spawner", make_props2_fish_spawner },
		{ "props2_fish_spawner_node", make_props2_fish_spawner_node },
		{ "props2_wall_fish", make_props2_wall_fish },
		{ "props2_barrels_fall_ST", make_props2_barrels_fall_ST },
		{ "props2_sign", make_props2_sign },
		{ "props2_lighthouse_beam", make_props2_lighthouse_beam },
		{ "props2_boat", make_props2_boat },
		{ "props2_buoy", make_props2_buoy },
		{ "props2_buoy_side", make_props2_buoy_side },
		{ "props2_deadguy_underwater", make_props2_deadguy_underwater },
		{ "props2_buoy_animate", make_props2_buoy_animate },
		{ "props2_gargoyle", make_props2_gargoyle },
		{ "props2_clothesline", make_props2_clothesline },
		{ "props2_plant_XL", make_props2_plant_XL },
		{ "props2_plant_SM", make_props2_plant_SM },
		{ "props2_boatphone", make_props2_boatphone },
		{ "props2_ashtray", make_props2_ashtray },
		{ "props2_lunch", make_props2_lunch },
		{ "props2_deadgal_headless", make_props2_deadgal_headless },
		{ "props2_plant_bush", make_props2_plant_bush },
		{ "props2_boat_animate", make_props2_boat_animate },
		{ "props2_helicopter_animate", make_props2_helicopter_animate },
		{ "props2_car_animate", make_props2_car_animate },
		{ "props2_car_topdown", make_props2_car_topdown },
		{ "props2_car_topup", make_props2_car_topup },
		{ "props2_plant_fern", make_props2_plant_fern },
		{ "props2_pinball_machine", make_props2_pinball_machine },
		{ "props2_barrels_PV_A", make_props2_barrels_PV_A },
		{ "props2_barrels_PV_C", make_props2_barrels_PV_C },
		{ "props2_barrels_PV_D", make_props2_barrels_PV_D },
		{ "props2_barrels_PV_E", make_props2_barrels_PV_E },
		{ "props2_barrels_PV_F", make_props2_barrels_PV_F },
		{ "light_chandelier", make_light_chandelier },
		{ "props2_air_train", make_props2_air_train },
		{ "props3_dead_louie", make_props3_dead_louie },
		{ "props3_cut_boss_player_animate", make_props3_cut_boss_player_animate },
		{ "props3_deco_fixture", make_props3_deco_fixture },
		{ "props3_cut_boss_chick_animate", make_props3_cut_boss_chick_animate },
		{ "props3_cut_train_run_animate", make_props3_cut_train_run_animate },
		{ "props3_cut_A_animate", make_props3_cut_A_animate },
		{ "props3_cut_B_animate", make_props3_cut_B_animate },
		{ "props3_cut_C_animate", make_props3_cut_C_animate },
		{ "props3_cut_D_animate", make_props3_cut_D_animate },
		{ "props3_cash_counter_animate", make_props3_cash_counter_animate },
		{ "props2_barrels_PV_B", make_props2_barrels_PV_B },
		{ "props3_decanter", make_props3_decanter },
		{ "props3_whiskey_glass", make_props3_whiskey_glass },
		{ "props3_barrels_fall_nikki_A", make_props3_barrels_fall_nikki_A },
		{ "props3_barrels_fall_nikki_B", make_props3_barrels_fall_nikki_B },
		{ "props3_cut_run_to_car_animate", make_props3_cut_run_to_car_animate },
		{ "props3_cut_final_animate", make_props3_cut_final_animate },
		{ "props3_cash", make_props3_cash },
		{ "props3_cut_truck_driver", make_props3_cut_truck_driver },
		{ "props3_cut_pinball_guy_animate", make_props3_cut_pinball_guy_animate },
		{ "lightflare", make_lightflare },
		{ "path_corner_cast", make_path_corner_cast },
		{ "pistol_mod_damage", make_pistol_mod_damage },
		{ "pistol_mod_rof", make_pistol_mod_rof },
		{ "pistol_mod_reload", make_pistol_mod_reload },
		{ "hmg_mod_cooling", make_hmg_mod_cooling },
		{ "sfx_beacon", make_sfx_beacon },
		{ "refl", make_refl },
		{ "dm_cashspawn", make_dm_cashspawn },
		{ "dm_safebag", make_dm_safebag },
		{ "dm_props_banner", make_dm_props_banner }
	};

	shared_ptr_entity IEntity::Make(const std::string_view& classname)
	{
		if (auto it = classes.find(classname); it != classes.end())
		{
			return it->second();
		}

		return nullptr;
	}
}
