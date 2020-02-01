#include "BaseEntity.h"
#include <string>
#include <unordered_map>
#include <memory>

#include "Entities/Item/AHealth.h"
#include "Entities/Item/AHealthSmall.h"
#include "Entities/Item/AHealthLarge.h"
#include "Entities/Item/AHealthMega.h"
#include "Entities/Info/APlayerStart.h"
#include "Entities/Info/APlayerDeathmatch.h"
#include "Entities/Info/APlayerCoop.h"
#include "Entities/Info/APlayerIntermission.h"
#include "Entities/Func/APlat.h"
#include "Entities/Func/AButton.h"
#include "Entities/Func/ADoor.h"
#include "Entities/Func/ADoorSecret.h"
#include "Entities/Func/ADoorRotating.h"
#include "Entities/Func/ARotating.h"
#include "Entities/Func/ATrain.h"
#include "Entities/Func/AWater.h"
#include "Entities/Func/AConveyor.h"
#include "Entities/Func/AAreaportal.h"
#include "Entities/Func/AClock.h"
#include "Entities/Func/AWall.h"
#include "Entities/Func/AObject.h"
#include "Entities/Func/ATimer.h"
#include "Entities/Func/AExplosive.h"
#include "Entities/Func/AKillbox.h"
#include "Entities/Func/AObjectRepair.h"
#include "Entities/Rotating/ALight.h"
#include "Entities/Trigger/AAlways.h"
#include "Entities/Trigger/AOnce.h"
#include "Entities/Trigger/AMultiple.h"
#include "Entities/Trigger/ARelay.h"
#include "Entities/Trigger/APush.h"
#include "Entities/Trigger/AHurt.h"
#include "Entities/Trigger/AKey.h"
#include "Entities/Trigger/ACounter.h"
#include "Entities/Trigger/AElevator.h"
#include "Entities/Trigger/AGravity.h"
#include "Entities/Trigger/AMonsterjump.h"
#include "Entities/Target/ATempEntity.h"
#include "Entities/Target/ASpeaker.h"
#include "Entities/Target/AExplosion.h"
#include "Entities/Target/AChangelevel.h"
#include "Entities/Target/ASecret.h"
#include "Entities/Target/AGoal.h"
#include "Entities/Target/ASplash.h"
#include "Entities/Target/ASpawner.h"
#include "Entities/Target/ABlaster.h"
#include "Entities/Target/ACrosslevelTrigger.h"
#include "Entities/Target/ACrosslevelTarget.h"
#include "Entities/Target/ALaser.h"
#include "Entities/Target/ALightramp.h"
#include "Entities/Target/AEarthquake.h"
#include "Entities/Target/ACharacter.h"
#include "Entities/Target/AString.h"
#include "Entities/Target/AMalLaser.h"
#include "Entities/AWorldspawn.h"
#include "Entities/AViewthing.h"
#include "Entities/ALight.h"
#include "Entities/Light/AMine1.h"
#include "Entities/Light/AMine2.h"
#include "Entities/Info/ANull.h"
#include "Entities/Func/AGroup.h"
#include "Entities/Info/ANotnull.h"
#include "Entities/Path/ACorner.h"
#include "Entities/AJunior.h"
#include "Entities/Misc/AExplobox.h"
#include "Entities/Misc/AGibArm.h"
#include "Entities/Misc/AGibLeg.h"
#include "Entities/Misc/AGibHead.h"
#include "Entities/Misc/ATeleporter.h"
#include "Entities/Misc/ATeleporterDest.h"
#include "Entities/Misc/AAmb4.h"
#include "Entities/Cast/APunk.h"
#include "Entities/Cast/AThug.h"
#include "Entities/Cast/AThugSit.h"
#include "Entities/Cast/ABitch.h"
#include "Entities/Cast/ADog.h"
#include "Entities/Cast/ARunt.h"
#include "Entities/Cast/ABumSit.h"
#include "Entities/Cast/AShorty.h"
#include "Entities/Cast/AWhore.h"
#include "Entities/Cast/APunkWindow.h"
#include "Entities/Cast/APunk2.h"
#include "Entities/Cast/ARosie.h"
#include "Entities/Ai/ABoundary.h"
#include "Entities/Ai/AEventHostile.h"
#include "Entities/Ai/AEventFollow.h"
#include "Entities/Ai/AGuard.h"
#include "Entities/Ai/ATerritory.h"
#include "Entities/Ai/ATriggerCharacter.h"
#include "Entities/Ai/ALockedDoor.h"
#include "Entities/Misc/ASkidrowRadio.h"
#include "Entities/Misc/ASkidrowAmbush.h"
#include "Entities/Misc/ASkidrowRadioRepeater.h"
#include "Entities/Ai/ATyFuseblown.h"
#include "Entities/Ai/AMokerNotinoffice.h"
#include "Entities/Misc/AGrunt.h"
#include "Entities/Misc/AFidela.h"
#include "Entities/Misc/ACar.h"
#include "Entities/Misc/ASmoke.h"
#include "Entities/AElps.h"
#include "Entities/Misc/AAlarm.h"
#include "Entities/Trigger/AHurtElectric.h"
#include "Entities/Pawn/AOMatic.h"
#include "Entities/Ai/ASafespot.h"
#include "Entities/Misc/ASkidrowAiReset.h"
#include "Entities/Ai/ACombatSpot.h"
#include "Entities/Misc/ASkidrowAfraid.h"
#include "Entities/Misc/ASteeltownAfraid.h"
#include "Entities/Misc/AKrokerAfraid.h"
#include "Entities/Rc/AInitiationObserver.h"
#include "Entities/Rc/AInitiationBrush.h"
#include "Entities/Misc/APvAfraid.h"
#include "Entities/Misc/ATyAfraid.h"
#include "Entities/Ai/ATyMoBoundry.h"
#include "Entities/Ai/ASyDykesBoundry.h"
#include "Entities/Misc/ASyAfraid.h"
#include "Entities/Ep/ASkidrowFlag.h"
#include "Entities/Ai/ASyOilcan.h"
#include "Entities/Ai/ATyValvehandle.h"
#include "Entities/Ai/APvFuseblown1.h"
#include "Entities/Ai/APvFuseblown2.h"
#include "Entities/Ai/APvDeadlouie.h"
#include "Entities/Ai/ASyBlefty.h"
#include "Entities/Misc/ABarryBitch.h"
#include "Entities/Misc/ACorkyFidelMdxPcx.h"
#include "Entities/Misc/ACorkyFidelMdxTga.h"
#include "Entities/Misc/ACutScene.h"
#include "Entities/Light/AFireEsm.h"
#include "Entities/Light/AFireSm.h"
#include "Entities/Light/AFireMed.h"
#include "Entities/Light/AFireLg.h"
#include "Entities/Smoke/AEsm.h"
#include "Entities/Smoke/ASm.h"
#include "Entities/Smoke/AMed.h"
#include "Entities/Smoke/ALg.h"
#include "Entities/Func/ATrainRotating.h"
#include "Entities/Func/ASubdoorBase.h"
#include "Entities/Func/ASubdoorHandle1.h"
#include "Entities/Func/ASubdoorHandle2.h"
#include "Entities/Props/ATrashcana.h"
#include "Entities/Props/ATrashcanFall.h"
#include "Entities/Props/AHydrant.h"
#include "Entities/Props/AAntenna1a.h"
#include "Entities/Props/AAntenna1b.h"
#include "Entities/Props/AAntenna1c.h"
#include "Entities/Props/AAntenna2a.h"
#include "Entities/Props/AAntenna2b.h"
#include "Entities/Props/AAntenna2c.h"
#include "Entities/Props/AAntenna3a.h"
#include "Entities/Props/AAntenna3b.h"
#include "Entities/Props/AAntenna3c.h"
#include "Entities/Props/AFan.h"
#include "Entities/Props/APhone.h"
#include "Entities/Props/AAircon.h"
#include "Entities/Props/ATableseta.h"
#include "Entities/Props/ARadio.h"
#include "Entities/Cast/ABuma.h"
#include "Entities/Cast/ABumb.h"
#include "Entities/Elements/ARaincloud.h"
#include "Entities/Elements/ASnowcloud.h"
#include "Entities/Misc/ACutsceneTrigger.h"
#include "Entities/Misc/ACutsceneCamera.h"
#include "Entities/Trigger/AUnlock.h"
#include "Entities/Props/AChair.h"
#include "Entities/Props/AExtinguishera.h"
#include "Entities/Props/AExtinguisherb.h"
#include "Entities/Light/ASconce.h"
#include "Entities/Props/AMotorcycle.h"
#include "Entities/Props/AAmmocrateBust.h"
#include "Entities/Props/AShelf.h"
#include "Entities/Props/AMattressa.h"
#include "Entities/Props/AMattressb.h"
#include "Entities/Props/AMattressc.h"
#include "Entities/Trigger/AMotorcycle.h"
#include "Entities/Props/ATv.h"
#include "Entities/Props/ASteamMachine.h"
#include "Entities/Light/ABulb.h"
#include "Entities/Props/ATrash.h"
#include "Entities/Props/AWallFall.h"
#include "Entities/Props/ATrashbottle.h"
#include "Entities/Props/ATrashwall.h"
#include "Entities/Props/ATrashpaper.h"
#include "Entities/Props/ATrashcorner.h"
#include "Entities/Props/ATrashbottleVert.h"
#include "Entities/Props/ABlimp.h"
#include "Entities/Misc/AUseCutscene.h"
#include "Entities/Props/AMotorcycleRunaway.h"
#include "Entities/Trigger/AHurtFire.h"
#include "Entities/Props/AShelfFall.h"
#include "Entities/Target/AFire.h"
#include "Entities/Props/ARat.h"
#include "Entities/Props/ARatSpawner.h"
#include "Entities/Props/ARatSpawnerNode.h"
#include "Entities/Target/AFlamethrower.h"
#include "Entities/Light/ADecoSconce.h"
#include "Entities/Light/APendant.h"
#include "Entities/Props/AShelfbFall.h"
#include "Entities/Func/ALift.h"
#include "Entities/Props/ARoofVent.h"
#include "Entities/Props/ARatTrigger.h"
#include "Entities/Props2/ATruckDie.h"
#include "Entities/Props/AColaMachine.h"
#include "Entities/Props/ACigMachine.h"
#include "Entities/Props2/ABarrelsFalla.h"
#include "Entities/Props2/ABarrelsFallb.h"
#include "Entities/Props2/AClubcouch.h"
#include "Entities/Props2/AClubchair.h"
#include "Entities/Props2/AVasea.h"
#include "Entities/Props2/AVaseb.h"
#include "Entities/Props2/AChairConf.h"
#include "Entities/Props2/AShelfMetalAFall.h"
#include "Entities/Props2/AShelfMetalBFall.h"
#include "Entities/Props2/ADeadguy.h"
#include "Entities/Props2/AChairPush.h"
#include "Entities/Props/ACrateBust32.h"
#include "Entities/Props/ACrateBust48.h"
#include "Entities/Props/ACrateBust64.h"
#include "Entities/Props2/AFlag.h"
#include "Entities/Props2/AFish.h"
#include "Entities/Props2/AFishTrigger.h"
#include "Entities/Props2/AFishSpawner.h"
#include "Entities/Props2/AFishSpawnerNode.h"
#include "Entities/Props2/AWallFish.h"
#include "Entities/Props2/ABarrelsFallSt.h"
#include "Entities/Props2/ASign.h"
#include "Entities/Props2/ALighthouseBeam.h"
#include "Entities/Props2/ABoat.h"
#include "Entities/Props2/ABuoy.h"
#include "Entities/Props2/ABuoySide.h"
#include "Entities/Props2/ADeadguyUnderwater.h"
#include "Entities/Props2/ABuoyAnimate.h"
#include "Entities/Props2/AGargoyle.h"
#include "Entities/Props2/AClothesline.h"
#include "Entities/Props2/APlantXl.h"
#include "Entities/Props2/APlantSm.h"
#include "Entities/Props2/ABoatphone.h"
#include "Entities/Props2/AAshtray.h"
#include "Entities/Props2/ALunch.h"
#include "Entities/Props2/ADeadgalHeadless.h"
#include "Entities/Props2/APlantBush.h"
#include "Entities/Props2/ABoatAnimate.h"
#include "Entities/Props2/AHelicopterAnimate.h"
#include "Entities/Props2/ACarAnimate.h"
#include "Entities/Props2/ACarTopdown.h"
#include "Entities/Props2/ACarTopup.h"
#include "Entities/Props2/APlantFern.h"
#include "Entities/Props2/APinballMachine.h"
#include "Entities/Props2/ABarrelsPvA.h"
#include "Entities/Props2/ABarrelsPvC.h"
#include "Entities/Props2/ABarrelsPvD.h"
#include "Entities/Props2/ABarrelsPvE.h"
#include "Entities/Props2/ABarrelsPvF.h"
#include "Entities/Light/AChandelier.h"
#include "Entities/Props2/AAirTrain.h"
#include "Entities/Props3/ADeadLouie.h"
#include "Entities/Props3/ACutBossPlayerAnimate.h"
#include "Entities/Props3/ADecoFixture.h"
#include "Entities/Props3/ACutBossChickAnimate.h"
#include "Entities/Props3/ACutTrainRunAnimate.h"
#include "Entities/Props3/ACutAAnimate.h"
#include "Entities/Props3/ACutBAnimate.h"
#include "Entities/Props3/ACutCAnimate.h"
#include "Entities/Props3/ACutDAnimate.h"
#include "Entities/Props3/ACashCounterAnimate.h"
#include "Entities/Props2/ABarrelsPvB.h"
#include "Entities/Props3/ADecanter.h"
#include "Entities/Props3/AWhiskeyGlass.h"
#include "Entities/Props3/ABarrelsFallNikkiA.h"
#include "Entities/Props3/ABarrelsFallNikkiB.h"
#include "Entities/Props3/ACutRunToCarAnimate.h"
#include "Entities/Props3/ACutFinalAnimate.h"
#include "Entities/Props3/ACash.h"
#include "Entities/Props3/ACutTruckDriver.h"
#include "Entities/Props3/ACutPinballGuyAnimate.h"
#include "Entities/ALightflare.h"
#include "Entities/Path/ACornerCast.h"
#include "Entities/Pistol/AModDamage.h"
#include "Entities/Pistol/AModRof.h"
#include "Entities/Pistol/AModReload.h"
#include "Entities/Hmg/AModCooling.h"
#include "Entities/Sfx/ABeacon.h"
#include "Entities/ARefl.h"
#include "Entities/Dm/ACashspawn.h"
#include "Entities/Dm/ASafebag.h"
#include "Entities/Dm/APropsBanner.h"

namespace Freeking
{
	BaseEntity::SharedPtr make_item_health() { return std::make_shared<Entity::Item::AHealth>(); }
	BaseEntity::SharedPtr make_item_health_small() { return std::make_shared<Entity::Item::AHealthSmall>(); }
	BaseEntity::SharedPtr make_item_health_large() { return std::make_shared<Entity::Item::AHealthLarge>(); }
	BaseEntity::SharedPtr make_item_health_mega() { return std::make_shared<Entity::Item::AHealthMega>(); }
	BaseEntity::SharedPtr make_info_player_start() { return std::make_shared<Entity::Info::APlayerStart>(); }
	BaseEntity::SharedPtr make_info_player_deathmatch() { return std::make_shared<Entity::Info::APlayerDeathmatch>(); }
	BaseEntity::SharedPtr make_info_player_coop() { return std::make_shared<Entity::Info::APlayerCoop>(); }
	BaseEntity::SharedPtr make_info_player_intermission() { return std::make_shared<Entity::Info::APlayerIntermission>(); }
	BaseEntity::SharedPtr make_func_plat() { return std::make_shared<Entity::Func::APlat>(); }
	BaseEntity::SharedPtr make_func_button() { return std::make_shared<Entity::Func::AButton>(); }
	BaseEntity::SharedPtr make_func_door() { return std::make_shared<Entity::Func::ADoor>(); }
	BaseEntity::SharedPtr make_func_door_secret() { return std::make_shared<Entity::Func::ADoorSecret>(); }
	BaseEntity::SharedPtr make_func_door_rotating() { return std::make_shared<Entity::Func::ADoorRotating>(); }
	BaseEntity::SharedPtr make_func_rotating() { return std::make_shared<Entity::Func::ARotating>(); }
	BaseEntity::SharedPtr make_func_train() { return std::make_shared<Entity::Func::ATrain>(); }
	BaseEntity::SharedPtr make_func_water() { return std::make_shared<Entity::Func::AWater>(); }
	BaseEntity::SharedPtr make_func_conveyor() { return std::make_shared<Entity::Func::AConveyor>(); }
	BaseEntity::SharedPtr make_func_areaportal() { return std::make_shared<Entity::Func::AAreaportal>(); }
	BaseEntity::SharedPtr make_func_clock() { return std::make_shared<Entity::Func::AClock>(); }
	BaseEntity::SharedPtr make_func_wall() { return std::make_shared<Entity::Func::AWall>(); }
	BaseEntity::SharedPtr make_func_object() { return std::make_shared<Entity::Func::AObject>(); }
	BaseEntity::SharedPtr make_func_timer() { return std::make_shared<Entity::Func::ATimer>(); }
	BaseEntity::SharedPtr make_func_explosive() { return std::make_shared<Entity::Func::AExplosive>(); }
	BaseEntity::SharedPtr make_func_killbox() { return std::make_shared<Entity::Func::AKillbox>(); }
	BaseEntity::SharedPtr make_func_object_repair() { return std::make_shared<Entity::Func::AObjectRepair>(); }
	BaseEntity::SharedPtr make_rotating_light() { return std::make_shared<Entity::Rotating::ALight>(); }
	BaseEntity::SharedPtr make_trigger_always() { return std::make_shared<Entity::Trigger::AAlways>(); }
	BaseEntity::SharedPtr make_trigger_once() { return std::make_shared<Entity::Trigger::AOnce>(); }
	BaseEntity::SharedPtr make_trigger_multiple() { return std::make_shared<Entity::Trigger::AMultiple>(); }
	BaseEntity::SharedPtr make_trigger_relay() { return std::make_shared<Entity::Trigger::ARelay>(); }
	BaseEntity::SharedPtr make_trigger_push() { return std::make_shared<Entity::Trigger::APush>(); }
	BaseEntity::SharedPtr make_trigger_hurt() { return std::make_shared<Entity::Trigger::AHurt>(); }
	BaseEntity::SharedPtr make_trigger_key() { return std::make_shared<Entity::Trigger::AKey>(); }
	BaseEntity::SharedPtr make_trigger_counter() { return std::make_shared<Entity::Trigger::ACounter>(); }
	BaseEntity::SharedPtr make_trigger_elevator() { return std::make_shared<Entity::Trigger::AElevator>(); }
	BaseEntity::SharedPtr make_trigger_gravity() { return std::make_shared<Entity::Trigger::AGravity>(); }
	BaseEntity::SharedPtr make_trigger_monsterjump() { return std::make_shared<Entity::Trigger::AMonsterjump>(); }
	BaseEntity::SharedPtr make_target_temp_entity() { return std::make_shared<Entity::Target::ATempEntity>(); }
	BaseEntity::SharedPtr make_target_speaker() { return std::make_shared<Entity::Target::ASpeaker>(); }
	BaseEntity::SharedPtr make_target_explosion() { return std::make_shared<Entity::Target::AExplosion>(); }
	BaseEntity::SharedPtr make_target_changelevel() { return std::make_shared<Entity::Target::AChangelevel>(); }
	BaseEntity::SharedPtr make_target_secret() { return std::make_shared<Entity::Target::ASecret>(); }
	BaseEntity::SharedPtr make_target_goal() { return std::make_shared<Entity::Target::AGoal>(); }
	BaseEntity::SharedPtr make_target_splash() { return std::make_shared<Entity::Target::ASplash>(); }
	BaseEntity::SharedPtr make_target_spawner() { return std::make_shared<Entity::Target::ASpawner>(); }
	BaseEntity::SharedPtr make_target_blaster() { return std::make_shared<Entity::Target::ABlaster>(); }
	BaseEntity::SharedPtr make_target_crosslevel_trigger() { return std::make_shared<Entity::Target::ACrosslevelTrigger>(); }
	BaseEntity::SharedPtr make_target_crosslevel_target() { return std::make_shared<Entity::Target::ACrosslevelTarget>(); }
	BaseEntity::SharedPtr make_target_laser() { return std::make_shared<Entity::Target::ALaser>(); }
	BaseEntity::SharedPtr make_target_lightramp() { return std::make_shared<Entity::Target::ALightramp>(); }
	BaseEntity::SharedPtr make_target_earthquake() { return std::make_shared<Entity::Target::AEarthquake>(); }
	BaseEntity::SharedPtr make_target_character() { return std::make_shared<Entity::Target::ACharacter>(); }
	BaseEntity::SharedPtr make_target_string() { return std::make_shared<Entity::Target::AString>(); }
	BaseEntity::SharedPtr make_target_mal_laser() { return std::make_shared<Entity::Target::AMalLaser>(); }
	BaseEntity::SharedPtr make_worldspawn() { return std::make_shared<Entity::AWorldspawn>(); }
	BaseEntity::SharedPtr make_viewthing() { return std::make_shared<Entity::AViewthing>(); }
	BaseEntity::SharedPtr make_light() { return std::make_shared<Entity::ALight>(); }
	BaseEntity::SharedPtr make_light_mine1() { return std::make_shared<Entity::Light::AMine1>(); }
	BaseEntity::SharedPtr make_light_mine2() { return std::make_shared<Entity::Light::AMine2>(); }
	BaseEntity::SharedPtr make_info_null() { return std::make_shared<Entity::Info::ANull>(); }
	BaseEntity::SharedPtr make_func_group() { return std::make_shared<Entity::Func::AGroup>(); }
	BaseEntity::SharedPtr make_info_notnull() { return std::make_shared<Entity::Info::ANotnull>(); }
	BaseEntity::SharedPtr make_path_corner() { return std::make_shared<Entity::Path::ACorner>(); }
	BaseEntity::SharedPtr make_junior() { return std::make_shared<Entity::AJunior>(); }
	BaseEntity::SharedPtr make_misc_explobox() { return std::make_shared<Entity::Misc::AExplobox>(); }
	BaseEntity::SharedPtr make_misc_gib_arm() { return std::make_shared<Entity::Misc::AGibArm>(); }
	BaseEntity::SharedPtr make_misc_gib_leg() { return std::make_shared<Entity::Misc::AGibLeg>(); }
	BaseEntity::SharedPtr make_misc_gib_head() { return std::make_shared<Entity::Misc::AGibHead>(); }
	BaseEntity::SharedPtr make_misc_teleporter() { return std::make_shared<Entity::Misc::ATeleporter>(); }
	BaseEntity::SharedPtr make_misc_teleporter_dest() { return std::make_shared<Entity::Misc::ATeleporterDest>(); }
	BaseEntity::SharedPtr make_misc_amb4() { return std::make_shared<Entity::Misc::AAmb4>(); }
	BaseEntity::SharedPtr make_cast_punk() { return std::make_shared<Entity::Cast::APunk>(); }
	BaseEntity::SharedPtr make_cast_thug() { return std::make_shared<Entity::Cast::AThug>(); }
	BaseEntity::SharedPtr make_cast_thug_sit() { return std::make_shared<Entity::Cast::AThugSit>(); }
	BaseEntity::SharedPtr make_cast_bitch() { return std::make_shared<Entity::Cast::ABitch>(); }
	BaseEntity::SharedPtr make_cast_dog() { return std::make_shared<Entity::Cast::ADog>(); }
	BaseEntity::SharedPtr make_cast_runt() { return std::make_shared<Entity::Cast::ARunt>(); }
	BaseEntity::SharedPtr make_cast_bum_sit() { return std::make_shared<Entity::Cast::ABumSit>(); }
	BaseEntity::SharedPtr make_cast_shorty() { return std::make_shared<Entity::Cast::AShorty>(); }
	BaseEntity::SharedPtr make_cast_whore() { return std::make_shared<Entity::Cast::AWhore>(); }
	BaseEntity::SharedPtr make_cast_punk_window() { return std::make_shared<Entity::Cast::APunkWindow>(); }
	BaseEntity::SharedPtr make_cast_punk2() { return std::make_shared<Entity::Cast::APunk2>(); }
	BaseEntity::SharedPtr make_cast_rosie() { return std::make_shared<Entity::Cast::ARosie>(); }
	BaseEntity::SharedPtr make_ai_boundary() { return std::make_shared<Entity::Ai::ABoundary>(); }
	BaseEntity::SharedPtr make_ai_event_hostile() { return std::make_shared<Entity::Ai::AEventHostile>(); }
	BaseEntity::SharedPtr make_ai_event_follow() { return std::make_shared<Entity::Ai::AEventFollow>(); }
	BaseEntity::SharedPtr make_ai_guard() { return std::make_shared<Entity::Ai::AGuard>(); }
	BaseEntity::SharedPtr make_ai_territory() { return std::make_shared<Entity::Ai::ATerritory>(); }
	BaseEntity::SharedPtr make_ai_trigger_character() { return std::make_shared<Entity::Ai::ATriggerCharacter>(); }
	BaseEntity::SharedPtr make_ai_locked_door() { return std::make_shared<Entity::Ai::ALockedDoor>(); }
	BaseEntity::SharedPtr make_misc_skidrow_radio() { return std::make_shared<Entity::Misc::ASkidrowRadio>(); }
	BaseEntity::SharedPtr make_misc_skidrow_ambush() { return std::make_shared<Entity::Misc::ASkidrowAmbush>(); }
	BaseEntity::SharedPtr make_misc_skidrow_radio_repeater() { return std::make_shared<Entity::Misc::ASkidrowRadioRepeater>(); }BaseEntity::SharedPtr make_ai_ty_fuseblown() { return std::make_shared<Entity::Ai::ATyFuseblown>(); }
	BaseEntity::SharedPtr make_ai_moker_notinoffice() { return std::make_shared<Entity::Ai::AMokerNotinoffice>(); }
	BaseEntity::SharedPtr make_misc_grunt() { return std::make_shared<Entity::Misc::AGrunt>(); }
	BaseEntity::SharedPtr make_misc_fidelA() { return std::make_shared<Entity::Misc::AFidela>(); }
	BaseEntity::SharedPtr make_misc_car() { return std::make_shared<Entity::Misc::ACar>(); }
	BaseEntity::SharedPtr make_misc_smoke() { return std::make_shared<Entity::Misc::ASmoke>(); }
	BaseEntity::SharedPtr make_elps() { return std::make_shared<Entity::AElps>(); }
	BaseEntity::SharedPtr make_misc_alarm() { return std::make_shared<Entity::Misc::AAlarm>(); }
	BaseEntity::SharedPtr make_trigger_hurt_electric() { return std::make_shared<Entity::Trigger::AHurtElectric>(); }
	BaseEntity::SharedPtr make_pawn_o_matic() { return std::make_shared<Entity::Pawn::AOMatic>(); }
	BaseEntity::SharedPtr make_ai_safespot() { return std::make_shared<Entity::Ai::ASafespot>(); }
	BaseEntity::SharedPtr make_misc_skidrow_ai_reset() { return std::make_shared<Entity::Misc::ASkidrowAiReset>(); }
	BaseEntity::SharedPtr make_ai_combat_spot() { return std::make_shared<Entity::Ai::ACombatSpot>(); }
	BaseEntity::SharedPtr make_misc_skidrow_afraid() { return std::make_shared<Entity::Misc::ASkidrowAfraid>(); }
	BaseEntity::SharedPtr make_misc_steeltown_afraid() { return std::make_shared<Entity::Misc::ASteeltownAfraid>(); }
	BaseEntity::SharedPtr make_misc_kroker_afraid() { return std::make_shared<Entity::Misc::AKrokerAfraid>(); }
	BaseEntity::SharedPtr make_rc_initiation_observer() { return std::make_shared<Entity::Rc::AInitiationObserver>(); }
	BaseEntity::SharedPtr make_rc_initiation_brush() { return std::make_shared<Entity::Rc::AInitiationBrush>(); }
	BaseEntity::SharedPtr make_misc_pv_afraid() { return std::make_shared<Entity::Misc::APvAfraid>(); }
	BaseEntity::SharedPtr make_misc_ty_afraid() { return std::make_shared<Entity::Misc::ATyAfraid>(); }
	BaseEntity::SharedPtr make_ai_ty_mo_boundry() { return std::make_shared<Entity::Ai::ATyMoBoundry>(); }
	BaseEntity::SharedPtr make_ai_sy_dykes_boundry() { return std::make_shared<Entity::Ai::ASyDykesBoundry>(); }
	BaseEntity::SharedPtr make_misc_sy_afraid() { return std::make_shared<Entity::Misc::ASyAfraid>(); }
	BaseEntity::SharedPtr make_ep_skidrow_flag() { return std::make_shared<Entity::Ep::ASkidrowFlag>(); }
	BaseEntity::SharedPtr make_ai_sy_oilcan() { return std::make_shared<Entity::Ai::ASyOilcan>(); }
	BaseEntity::SharedPtr make_ai_ty_valvehandle() { return std::make_shared<Entity::Ai::ATyValvehandle>(); }
	BaseEntity::SharedPtr make_ai_pv_fuseblown1() { return std::make_shared<Entity::Ai::APvFuseblown1>(); }
	BaseEntity::SharedPtr make_ai_pv_fuseblown2() { return std::make_shared<Entity::Ai::APvFuseblown2>(); }
	BaseEntity::SharedPtr make_ai_pv_deadlouie() { return std::make_shared<Entity::Ai::APvDeadlouie>(); }
	BaseEntity::SharedPtr make_ai_sy_blefty() { return std::make_shared<Entity::Ai::ASyBlefty>(); }
	BaseEntity::SharedPtr make_misc_barry_bitch() { return std::make_shared<Entity::Misc::ABarryBitch>(); }
	BaseEntity::SharedPtr make_misc_corky_fidel_mdx_pcx() { return std::make_shared<Entity::Misc::ACorkyFidelMdxPcx>(); }
	BaseEntity::SharedPtr make_misc_corky_fidel_mdx_tga() { return std::make_shared<Entity::Misc::ACorkyFidelMdxTga>(); }
	BaseEntity::SharedPtr make_misc_cut_scene() { return std::make_shared<Entity::Misc::ACutScene>(); }
	BaseEntity::SharedPtr make_light_fire_esm() { return std::make_shared<Entity::Light::AFireEsm>(); }
	BaseEntity::SharedPtr make_light_fire_sm() { return std::make_shared<Entity::Light::AFireSm>(); }
	BaseEntity::SharedPtr make_light_fire_med() { return std::make_shared<Entity::Light::AFireMed>(); }
	BaseEntity::SharedPtr make_light_fire_lg() { return std::make_shared<Entity::Light::AFireLg>(); }
	BaseEntity::SharedPtr make_smoke_esm() { return std::make_shared<Entity::Smoke::AEsm>(); }
	BaseEntity::SharedPtr make_smoke_sm() { return std::make_shared<Entity::Smoke::ASm>(); }
	BaseEntity::SharedPtr make_smoke_med() { return std::make_shared<Entity::Smoke::AMed>(); }
	BaseEntity::SharedPtr make_smoke_lg() { return std::make_shared<Entity::Smoke::ALg>(); }
	BaseEntity::SharedPtr make_func_train_rotating() { return std::make_shared<Entity::Func::ATrainRotating>(); }
	BaseEntity::SharedPtr make_func_subdoor_base() { return std::make_shared<Entity::Func::ASubdoorBase>(); }
	BaseEntity::SharedPtr make_func_subdoor_handle1() { return std::make_shared<Entity::Func::ASubdoorHandle1>(); }
	BaseEntity::SharedPtr make_func_subdoor_handle2() { return std::make_shared<Entity::Func::ASubdoorHandle2>(); }
	BaseEntity::SharedPtr make_props_trashcanA() { return std::make_shared<Entity::Props::ATrashcana>(); }
	BaseEntity::SharedPtr make_props_trashcan_fall() { return std::make_shared<Entity::Props::ATrashcanFall>(); }
	BaseEntity::SharedPtr make_props_hydrant() { return std::make_shared<Entity::Props::AHydrant>(); }
	BaseEntity::SharedPtr make_props_antenna1a() { return std::make_shared<Entity::Props::AAntenna1a>(); }
	BaseEntity::SharedPtr make_props_antenna1b() { return std::make_shared<Entity::Props::AAntenna1b>(); }
	BaseEntity::SharedPtr make_props_antenna1c() { return std::make_shared<Entity::Props::AAntenna1c>(); }
	BaseEntity::SharedPtr make_props_antenna2a() { return std::make_shared<Entity::Props::AAntenna2a>(); }
	BaseEntity::SharedPtr make_props_antenna2b() { return std::make_shared<Entity::Props::AAntenna2b>(); }
	BaseEntity::SharedPtr make_props_antenna2c() { return std::make_shared<Entity::Props::AAntenna2c>(); }
	BaseEntity::SharedPtr make_props_antenna3a() { return std::make_shared<Entity::Props::AAntenna3a>(); }
	BaseEntity::SharedPtr make_props_antenna3b() { return std::make_shared<Entity::Props::AAntenna3b>(); }
	BaseEntity::SharedPtr make_props_antenna3c() { return std::make_shared<Entity::Props::AAntenna3c>(); }
	BaseEntity::SharedPtr make_props_fan() { return std::make_shared<Entity::Props::AFan>(); }
	BaseEntity::SharedPtr make_props_phone() { return std::make_shared<Entity::Props::APhone>(); }
	BaseEntity::SharedPtr make_props_aircon() { return std::make_shared<Entity::Props::AAircon>(); }
	BaseEntity::SharedPtr make_props_tablesetA() { return std::make_shared<Entity::Props::ATableseta>(); }
	BaseEntity::SharedPtr make_props_radio() { return std::make_shared<Entity::Props::ARadio>(); }
	BaseEntity::SharedPtr make_cast_buma() { return std::make_shared<Entity::Cast::ABuma>(); }
	BaseEntity::SharedPtr make_cast_bumb() { return std::make_shared<Entity::Cast::ABumb>(); }
	BaseEntity::SharedPtr make_elements_raincloud() { return std::make_shared<Entity::Elements::ARaincloud>(); }
	BaseEntity::SharedPtr make_elements_snowcloud() { return std::make_shared<Entity::Elements::ASnowcloud>(); }
	BaseEntity::SharedPtr make_misc_cutscene_trigger() { return std::make_shared<Entity::Misc::ACutsceneTrigger>(); }
	BaseEntity::SharedPtr make_misc_cutscene_camera() { return std::make_shared<Entity::Misc::ACutsceneCamera>(); }
	BaseEntity::SharedPtr make_trigger_unlock() { return std::make_shared<Entity::Trigger::AUnlock>(); }
	BaseEntity::SharedPtr make_props_chair() { return std::make_shared<Entity::Props::AChair>(); }
	BaseEntity::SharedPtr make_props_extinguisherA() { return std::make_shared<Entity::Props::AExtinguishera>(); }
	BaseEntity::SharedPtr make_props_extinguisherB() { return std::make_shared<Entity::Props::AExtinguisherb>(); }
	BaseEntity::SharedPtr make_light_sconce() { return std::make_shared<Entity::Light::ASconce>(); }
	BaseEntity::SharedPtr make_props_motorcycle() { return std::make_shared<Entity::Props::AMotorcycle>(); }
	BaseEntity::SharedPtr make_props_ammocrate_bust() { return std::make_shared<Entity::Props::AAmmocrateBust>(); }
	BaseEntity::SharedPtr make_props_shelf() { return std::make_shared<Entity::Props::AShelf>(); }
	BaseEntity::SharedPtr make_props_mattressA() { return std::make_shared<Entity::Props::AMattressa>(); }
	BaseEntity::SharedPtr make_props_mattressB() { return std::make_shared<Entity::Props::AMattressb>(); }
	BaseEntity::SharedPtr make_props_mattressC() { return std::make_shared<Entity::Props::AMattressc>(); }
	BaseEntity::SharedPtr make_trigger_motorcycle() { return std::make_shared<Entity::Trigger::AMotorcycle>(); }
	BaseEntity::SharedPtr make_props_tv() { return std::make_shared<Entity::Props::ATv>(); }
	BaseEntity::SharedPtr make_props_steam_machine() { return std::make_shared<Entity::Props::ASteamMachine>(); }
	BaseEntity::SharedPtr make_light_bulb() { return std::make_shared<Entity::Light::ABulb>(); }
	BaseEntity::SharedPtr make_props_trash() { return std::make_shared<Entity::Props::ATrash>(); }
	BaseEntity::SharedPtr make_props_wall_fall() { return std::make_shared<Entity::Props::AWallFall>(); }
	BaseEntity::SharedPtr make_props_trashbottle() { return std::make_shared<Entity::Props::ATrashbottle>(); }
	BaseEntity::SharedPtr make_props_trashwall() { return std::make_shared<Entity::Props::ATrashwall>(); }
	BaseEntity::SharedPtr make_props_trashpaper() { return std::make_shared<Entity::Props::ATrashpaper>(); }
	BaseEntity::SharedPtr make_props_trashcorner() { return std::make_shared<Entity::Props::ATrashcorner>(); }
	BaseEntity::SharedPtr make_props_trashbottle_vert() { return std::make_shared<Entity::Props::ATrashbottleVert>(); }
	BaseEntity::SharedPtr make_props_blimp() { return std::make_shared<Entity::Props::ABlimp>(); }
	BaseEntity::SharedPtr make_misc_use_cutscene() { return std::make_shared<Entity::Misc::AUseCutscene>(); }
	BaseEntity::SharedPtr make_props_motorcycle_runaway() { return std::make_shared<Entity::Props::AMotorcycleRunaway>(); }
	BaseEntity::SharedPtr make_trigger_hurt_fire() { return std::make_shared<Entity::Trigger::AHurtFire>(); }
	BaseEntity::SharedPtr make_props_shelf_fall() { return std::make_shared<Entity::Props::AShelfFall>(); }
	BaseEntity::SharedPtr make_target_fire() { return std::make_shared<Entity::Target::AFire>(); }
	BaseEntity::SharedPtr make_props_rat() { return std::make_shared<Entity::Props::ARat>(); }
	BaseEntity::SharedPtr make_props_rat_spawner() { return std::make_shared<Entity::Props::ARatSpawner>(); }
	BaseEntity::SharedPtr make_props_rat_spawner_node() { return std::make_shared<Entity::Props::ARatSpawnerNode>(); }
	BaseEntity::SharedPtr make_target_flamethrower() { return std::make_shared<Entity::Target::AFlamethrower>(); }
	BaseEntity::SharedPtr make_light_deco_sconce() { return std::make_shared<Entity::Light::ADecoSconce>(); }
	BaseEntity::SharedPtr make_light_pendant() { return std::make_shared<Entity::Light::APendant>(); }
	BaseEntity::SharedPtr make_props_shelfB_fall() { return std::make_shared<Entity::Props::AShelfbFall>(); }
	BaseEntity::SharedPtr make_func_lift() { return std::make_shared<Entity::Func::ALift>(); }
	BaseEntity::SharedPtr make_props_roof_vent() { return std::make_shared<Entity::Props::ARoofVent>(); }
	BaseEntity::SharedPtr make_props_rat_trigger() { return std::make_shared<Entity::Props::ARatTrigger>(); }
	BaseEntity::SharedPtr make_props2_truck_die() { return std::make_shared<Entity::Props2::ATruckDie>(); }
	BaseEntity::SharedPtr make_props_cola_machine() { return std::make_shared<Entity::Props::AColaMachine>(); }
	BaseEntity::SharedPtr make_props_cig_machine() { return std::make_shared<Entity::Props::ACigMachine>(); }
	BaseEntity::SharedPtr make_props2_barrels_fallA() { return std::make_shared<Entity::Props2::ABarrelsFalla>(); }
	BaseEntity::SharedPtr make_props2_barrels_fallB() { return std::make_shared<Entity::Props2::ABarrelsFallb>(); }
	BaseEntity::SharedPtr make_props2_clubcouch() { return std::make_shared<Entity::Props2::AClubcouch>(); }
	BaseEntity::SharedPtr make_props2_clubchair() { return std::make_shared<Entity::Props2::AClubchair>(); }
	BaseEntity::SharedPtr make_props2_vaseA() { return std::make_shared<Entity::Props2::AVasea>(); }
	BaseEntity::SharedPtr make_props2_vaseB() { return std::make_shared<Entity::Props2::AVaseb>(); }
	BaseEntity::SharedPtr make_props2_chair_conf() { return std::make_shared<Entity::Props2::AChairConf>(); }
	BaseEntity::SharedPtr make_props2_shelf_metal_A_fall() { return std::make_shared<Entity::Props2::AShelfMetalAFall>(); }
	BaseEntity::SharedPtr make_props2_shelf_metal_B_fall() { return std::make_shared<Entity::Props2::AShelfMetalBFall>(); }
	BaseEntity::SharedPtr make_props2_deadguy() { return std::make_shared<Entity::Props2::ADeadguy>(); }
	BaseEntity::SharedPtr make_props2_chair_push() { return std::make_shared<Entity::Props2::AChairPush>(); }
	BaseEntity::SharedPtr make_props_crate_bust_32() { return std::make_shared<Entity::Props::ACrateBust32>(); }
	BaseEntity::SharedPtr make_props_crate_bust_48() { return std::make_shared<Entity::Props::ACrateBust48>(); }
	BaseEntity::SharedPtr make_props_crate_bust_64() { return std::make_shared<Entity::Props::ACrateBust64>(); }
	BaseEntity::SharedPtr make_props2_flag() { return std::make_shared<Entity::Props2::AFlag>(); }
	BaseEntity::SharedPtr make_props2_fish() { return std::make_shared<Entity::Props2::AFish>(); }
	BaseEntity::SharedPtr make_props2_fish_trigger() { return std::make_shared<Entity::Props2::AFishTrigger>(); }
	BaseEntity::SharedPtr make_props2_fish_spawner() { return std::make_shared<Entity::Props2::AFishSpawner>(); }
	BaseEntity::SharedPtr make_props2_fish_spawner_node() { return std::make_shared<Entity::Props2::AFishSpawnerNode>(); }
	BaseEntity::SharedPtr make_props2_wall_fish() { return std::make_shared<Entity::Props2::AWallFish>(); }
	BaseEntity::SharedPtr make_props2_barrels_fall_ST() { return std::make_shared<Entity::Props2::ABarrelsFallSt>(); }
	BaseEntity::SharedPtr make_props2_sign() { return std::make_shared<Entity::Props2::ASign>(); }
	BaseEntity::SharedPtr make_props2_lighthouse_beam() { return std::make_shared<Entity::Props2::ALighthouseBeam>(); }
	BaseEntity::SharedPtr make_props2_boat() { return std::make_shared<Entity::Props2::ABoat>(); }
	BaseEntity::SharedPtr make_props2_buoy() { return std::make_shared<Entity::Props2::ABuoy>(); }
	BaseEntity::SharedPtr make_props2_buoy_side() { return std::make_shared<Entity::Props2::ABuoySide>(); }
	BaseEntity::SharedPtr make_props2_deadguy_underwater() { return std::make_shared<Entity::Props2::ADeadguyUnderwater>(); }
	BaseEntity::SharedPtr make_props2_buoy_animate() { return std::make_shared<Entity::Props2::ABuoyAnimate>(); }
	BaseEntity::SharedPtr make_props2_gargoyle() { return std::make_shared<Entity::Props2::AGargoyle>(); }
	BaseEntity::SharedPtr make_props2_clothesline() { return std::make_shared<Entity::Props2::AClothesline>(); }
	BaseEntity::SharedPtr make_props2_plant_XL() { return std::make_shared<Entity::Props2::APlantXl>(); }
	BaseEntity::SharedPtr make_props2_plant_SM() { return std::make_shared<Entity::Props2::APlantSm>(); }
	BaseEntity::SharedPtr make_props2_boatphone() { return std::make_shared<Entity::Props2::ABoatphone>(); }
	BaseEntity::SharedPtr make_props2_ashtray() { return std::make_shared<Entity::Props2::AAshtray>(); }
	BaseEntity::SharedPtr make_props2_lunch() { return std::make_shared<Entity::Props2::ALunch>(); }
	BaseEntity::SharedPtr make_props2_deadgal_headless() { return std::make_shared<Entity::Props2::ADeadgalHeadless>(); }
	BaseEntity::SharedPtr make_props2_plant_bush() { return std::make_shared<Entity::Props2::APlantBush>(); }
	BaseEntity::SharedPtr make_props2_boat_animate() { return std::make_shared<Entity::Props2::ABoatAnimate>(); }
	BaseEntity::SharedPtr make_props2_helicopter_animate() { return std::make_shared<Entity::Props2::AHelicopterAnimate>(); }
	BaseEntity::SharedPtr make_props2_car_animate() { return std::make_shared<Entity::Props2::ACarAnimate>(); }
	BaseEntity::SharedPtr make_props2_car_topdown() { return std::make_shared<Entity::Props2::ACarTopdown>(); }
	BaseEntity::SharedPtr make_props2_car_topup() { return std::make_shared<Entity::Props2::ACarTopup>(); }
	BaseEntity::SharedPtr make_props2_plant_fern() { return std::make_shared<Entity::Props2::APlantFern>(); }
	BaseEntity::SharedPtr make_props2_pinball_machine() { return std::make_shared<Entity::Props2::APinballMachine>(); }
	BaseEntity::SharedPtr make_props2_barrels_PV_A() { return std::make_shared<Entity::Props2::ABarrelsPvA>(); }
	BaseEntity::SharedPtr make_props2_barrels_PV_C() { return std::make_shared<Entity::Props2::ABarrelsPvC>(); }
	BaseEntity::SharedPtr make_props2_barrels_PV_D() { return std::make_shared<Entity::Props2::ABarrelsPvD>(); }
	BaseEntity::SharedPtr make_props2_barrels_PV_E() { return std::make_shared<Entity::Props2::ABarrelsPvE>(); }
	BaseEntity::SharedPtr make_props2_barrels_PV_F() { return std::make_shared<Entity::Props2::ABarrelsPvF>(); }
	BaseEntity::SharedPtr make_light_chandelier() { return std::make_shared<Entity::Light::AChandelier>(); }
	BaseEntity::SharedPtr make_props2_air_train() { return std::make_shared<Entity::Props2::AAirTrain>(); }
	BaseEntity::SharedPtr make_props3_dead_louie() { return std::make_shared<Entity::Props3::ADeadLouie>(); }
	BaseEntity::SharedPtr make_props3_cut_boss_player_animate() { return std::make_shared<Entity::Props3::ACutBossPlayerAnimate>(); }
	BaseEntity::SharedPtr make_props3_deco_fixture() { return std::make_shared<Entity::Props3::ADecoFixture>(); }
	BaseEntity::SharedPtr make_props3_cut_boss_chick_animate() { return std::make_shared<Entity::Props3::ACutBossChickAnimate>(); }
	BaseEntity::SharedPtr make_props3_cut_train_run_animate() { return std::make_shared<Entity::Props3::ACutTrainRunAnimate>(); }
	BaseEntity::SharedPtr make_props3_cut_A_animate() { return std::make_shared<Entity::Props3::ACutAAnimate>(); }
	BaseEntity::SharedPtr make_props3_cut_B_animate() { return std::make_shared<Entity::Props3::ACutBAnimate>(); }
	BaseEntity::SharedPtr make_props3_cut_C_animate() { return std::make_shared<Entity::Props3::ACutCAnimate>(); }
	BaseEntity::SharedPtr make_props3_cut_D_animate() { return std::make_shared<Entity::Props3::ACutDAnimate>(); }
	BaseEntity::SharedPtr make_props3_cash_counter_animate() { return std::make_shared<Entity::Props3::ACashCounterAnimate>(); }BaseEntity::SharedPtr make_props2_barrels_PV_B() { return std::make_shared<Entity::Props2::ABarrelsPvB>(); }
	BaseEntity::SharedPtr make_props3_decanter() { return std::make_shared<Entity::Props3::ADecanter>(); }
	BaseEntity::SharedPtr make_props3_whiskey_glass() { return std::make_shared<Entity::Props3::AWhiskeyGlass>(); }
	BaseEntity::SharedPtr make_props3_barrels_fall_nikki_A() { return std::make_shared<Entity::Props3::ABarrelsFallNikkiA>(); }
	BaseEntity::SharedPtr make_props3_barrels_fall_nikki_B() { return std::make_shared<Entity::Props3::ABarrelsFallNikkiB>(); }
	BaseEntity::SharedPtr make_props3_cut_run_to_car_animate() { return std::make_shared<Entity::Props3::ACutRunToCarAnimate>(); }
	BaseEntity::SharedPtr make_props3_cut_final_animate() { return std::make_shared<Entity::Props3::ACutFinalAnimate>(); }
	BaseEntity::SharedPtr make_props3_cash() { return std::make_shared<Entity::Props3::ACash>(); }
	BaseEntity::SharedPtr make_props3_cut_truck_driver() { return std::make_shared<Entity::Props3::ACutTruckDriver>(); }
	BaseEntity::SharedPtr make_props3_cut_pinball_guy_animate() { return std::make_shared<Entity::Props3::ACutPinballGuyAnimate>(); }
	BaseEntity::SharedPtr make_lightflare() { return std::make_shared<Entity::ALightflare>(); }
	BaseEntity::SharedPtr make_path_corner_cast() { return std::make_shared<Entity::Path::ACornerCast>(); }
	BaseEntity::SharedPtr make_pistol_mod_damage() { return std::make_shared<Entity::Pistol::AModDamage>(); }
	BaseEntity::SharedPtr make_pistol_mod_rof() { return std::make_shared<Entity::Pistol::AModRof>(); }
	BaseEntity::SharedPtr make_pistol_mod_reload() { return std::make_shared<Entity::Pistol::AModReload>(); }
	BaseEntity::SharedPtr make_hmg_mod_cooling() { return std::make_shared<Entity::Hmg::AModCooling>(); }
	BaseEntity::SharedPtr make_sfx_beacon() { return std::make_shared<Entity::Sfx::ABeacon>(); }
	BaseEntity::SharedPtr make_refl() { return std::make_shared<Entity::ARefl>(); }
	BaseEntity::SharedPtr make_dm_cashspawn() { return std::make_shared<Entity::Dm::ACashspawn>(); }
	BaseEntity::SharedPtr make_dm_safebag() { return std::make_shared<Entity::Dm::ASafebag>(); }
	BaseEntity::SharedPtr make_dm_props_banner() { return std::make_shared<Entity::Dm::APropsBanner>(); }

	static const std::unordered_map<std::string_view, BaseEntity::SharedPtr(*)()> classes =
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

	BaseEntity::SharedPtr BaseEntity::Make(const std::string_view& classname)
	{
		if (auto it = classes.find(classname); it != classes.end())
		{
			return it->second();
		}

		return nullptr;
	}
}
