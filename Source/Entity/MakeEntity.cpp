#include "IEntity.h"
#include <string>
#include <unordered_map>
#include <memory>

namespace Freeking
{
	typedef std::shared_ptr<IEntity> shared_ptr_entity;

	shared_ptr_entity make_item_health() { return nullptr; }
	shared_ptr_entity make_item_health_small() { return nullptr; }
	shared_ptr_entity make_item_health_large() { return nullptr; }
	shared_ptr_entity make_item_health_mega() { return nullptr; }
	shared_ptr_entity make_info_player_start() { return nullptr; }
	shared_ptr_entity make_info_player_deathmatch() { return nullptr; }
	shared_ptr_entity make_info_player_coop() { return nullptr; }
	shared_ptr_entity make_info_player_intermission() { return nullptr; }
	shared_ptr_entity make_func_plat() { return nullptr; }
	shared_ptr_entity make_func_button() { return nullptr; }
	shared_ptr_entity make_func_door() { return nullptr; }
	shared_ptr_entity make_func_door_secret() { return nullptr; }
	shared_ptr_entity make_func_door_rotating() { return nullptr; }
	shared_ptr_entity make_func_rotating() { return nullptr; }
	shared_ptr_entity make_func_train() { return nullptr; }
	shared_ptr_entity make_func_water() { return nullptr; }
	shared_ptr_entity make_func_conveyor() { return nullptr; }
	shared_ptr_entity make_func_areaportal() { return nullptr; }
	shared_ptr_entity make_func_clock() { return nullptr; }
	shared_ptr_entity make_func_wall() { return nullptr; }
	shared_ptr_entity make_func_object() { return nullptr; }
	shared_ptr_entity make_func_timer() { return nullptr; }
	shared_ptr_entity make_func_explosive() { return nullptr; }
	shared_ptr_entity make_func_killbox() { return nullptr; }
	shared_ptr_entity make_func_object_repair() { return nullptr; }
	shared_ptr_entity make_rotating_light() { return nullptr; }
	shared_ptr_entity make_trigger_always() { return nullptr; }
	shared_ptr_entity make_trigger_once() { return nullptr; }
	shared_ptr_entity make_trigger_multiple() { return nullptr; }
	shared_ptr_entity make_trigger_relay() { return nullptr; }
	shared_ptr_entity make_trigger_push() { return nullptr; }
	shared_ptr_entity make_trigger_hurt() { return nullptr; }
	shared_ptr_entity make_trigger_key() { return nullptr; }
	shared_ptr_entity make_trigger_counter() { return nullptr; }
	shared_ptr_entity make_trigger_elevator() { return nullptr; }
	shared_ptr_entity make_trigger_gravity() { return nullptr; }
	shared_ptr_entity make_trigger_monsterjump() { return nullptr; }
	shared_ptr_entity make_target_temp_entity() { return nullptr; }
	shared_ptr_entity make_target_speaker() { return nullptr; }
	shared_ptr_entity make_target_explosion() { return nullptr; }
	shared_ptr_entity make_target_changelevel() { return nullptr; }
	shared_ptr_entity make_target_secret() { return nullptr; }
	shared_ptr_entity make_target_goal() { return nullptr; }
	shared_ptr_entity make_target_splash() { return nullptr; }
	shared_ptr_entity make_target_spawner() { return nullptr; }
	shared_ptr_entity make_target_blaster() { return nullptr; }
	shared_ptr_entity make_target_crosslevel_trigger() { return nullptr; }
	shared_ptr_entity make_target_crosslevel_target() { return nullptr; }
	shared_ptr_entity make_target_laser() { return nullptr; }
	shared_ptr_entity make_target_lightramp() { return nullptr; }
	shared_ptr_entity make_target_earthquake() { return nullptr; }
	shared_ptr_entity make_target_character() { return nullptr; }
	shared_ptr_entity make_target_string() { return nullptr; }
	shared_ptr_entity make_target_mal_laser() { return nullptr; }
	shared_ptr_entity make_worldspawn() { return nullptr; }
	shared_ptr_entity make_viewthing() { return nullptr; }
	shared_ptr_entity make_light() { return nullptr; }
	shared_ptr_entity make_light_mine1() { return nullptr; }
	shared_ptr_entity make_light_mine2() { return nullptr; }
	shared_ptr_entity make_info_null() { return nullptr; }
	shared_ptr_entity make_func_group() { return nullptr; }
	shared_ptr_entity make_info_notnull() { return nullptr; }
	shared_ptr_entity make_path_corner() { return nullptr; }
	shared_ptr_entity make_junior() { return nullptr; }
	shared_ptr_entity make_misc_explobox() { return nullptr; }
	shared_ptr_entity make_misc_gib_arm() { return nullptr; }
	shared_ptr_entity make_misc_gib_leg() { return nullptr; }
	shared_ptr_entity make_misc_gib_head() { return nullptr; }
	shared_ptr_entity make_misc_teleporter() { return nullptr; }
	shared_ptr_entity make_misc_teleporter_dest() { return nullptr; }
	shared_ptr_entity make_misc_amb4() { return nullptr; }
	shared_ptr_entity make_cast_punk() { return nullptr; }
	shared_ptr_entity make_cast_thug() { return nullptr; }
	shared_ptr_entity make_cast_thug_sit() { return nullptr; }
	shared_ptr_entity make_cast_bitch() { return nullptr; }
	shared_ptr_entity make_cast_dog() { return nullptr; }
	shared_ptr_entity make_cast_runt() { return nullptr; }
	shared_ptr_entity make_cast_bum_sit() { return nullptr; }
	shared_ptr_entity make_cast_shorty() { return nullptr; }
	shared_ptr_entity make_cast_whore() { return nullptr; }
	shared_ptr_entity make_cast_punk_window() { return nullptr; }
	shared_ptr_entity make_cast_punk2() { return nullptr; }
	shared_ptr_entity make_cast_rosie() { return nullptr; }
	shared_ptr_entity make_ai_boundary() { return nullptr; }
	shared_ptr_entity make_ai_event_hostile() { return nullptr; }
	shared_ptr_entity make_ai_event_follow() { return nullptr; }
	shared_ptr_entity make_ai_guard() { return nullptr; }
	shared_ptr_entity make_ai_territory() { return nullptr; }
	shared_ptr_entity make_ai_trigger_character() { return nullptr; }
	shared_ptr_entity make_ai_locked_door() { return nullptr; }
	shared_ptr_entity make_misc_skidrow_radio() { return nullptr; }
	shared_ptr_entity make_misc_skidrow_ambush() { return nullptr; }
	shared_ptr_entity make_misc_skidrow_radio_repeater() { return nullptr; }
	shared_ptr_entity make_ai_ty_fuseblown() { return nullptr; }
	shared_ptr_entity make_ai_moker_notinoffice() { return nullptr; }
	shared_ptr_entity make_misc_grunt() { return nullptr; }
	shared_ptr_entity make_misc_fidelA() { return nullptr; }
	shared_ptr_entity make_misc_car() { return nullptr; }
	shared_ptr_entity make_misc_smoke() { return nullptr; }
	shared_ptr_entity make_elps() { return nullptr; }
	shared_ptr_entity make_misc_alarm() { return nullptr; }
	shared_ptr_entity make_trigger_hurt_electric() { return nullptr; }
	shared_ptr_entity make_pawn_o_matic() { return nullptr; }
	shared_ptr_entity make_ai_safespot() { return nullptr; }
	shared_ptr_entity make_misc_skidrow_ai_reset() { return nullptr; }
	shared_ptr_entity make_ai_combat_spot() { return nullptr; }
	shared_ptr_entity make_misc_skidrow_afraid() { return nullptr; }
	shared_ptr_entity make_misc_steeltown_afraid() { return nullptr; }
	shared_ptr_entity make_misc_kroker_afraid() { return nullptr; }
	shared_ptr_entity make_rc_initiation_observer() { return nullptr; }
	shared_ptr_entity make_rc_initiation_brush() { return nullptr; }
	shared_ptr_entity make_misc_pv_afraid() { return nullptr; }
	shared_ptr_entity make_misc_ty_afraid() { return nullptr; }
	shared_ptr_entity make_ai_ty_mo_boundry() { return nullptr; }
	shared_ptr_entity make_ai_sy_dykes_boundry() { return nullptr; }
	shared_ptr_entity make_misc_sy_afraid() { return nullptr; }
	shared_ptr_entity make_ep_skidrow_flag() { return nullptr; }
	shared_ptr_entity make_ai_sy_oilcan() { return nullptr; }
	shared_ptr_entity make_ai_ty_valvehandle() { return nullptr; }
	shared_ptr_entity make_ai_pv_fuseblown1() { return nullptr; }
	shared_ptr_entity make_ai_pv_fuseblown2() { return nullptr; }
	shared_ptr_entity make_ai_pv_deadlouie() { return nullptr; }
	shared_ptr_entity make_ai_sy_blefty() { return nullptr; }
	shared_ptr_entity make_misc_barry_bitch() { return nullptr; }
	shared_ptr_entity make_misc_corky_fidel_mdx_pcx() { return nullptr; }
	shared_ptr_entity make_misc_corky_fidel_mdx_tga() { return nullptr; }
	shared_ptr_entity make_misc_cut_scene() { return nullptr; }
	shared_ptr_entity make_light_fire_esm() { return nullptr; }
	shared_ptr_entity make_light_fire_sm() { return nullptr; }
	shared_ptr_entity make_light_fire_med() { return nullptr; }
	shared_ptr_entity make_light_fire_lg() { return nullptr; }
	shared_ptr_entity make_smoke_esm() { return nullptr; }
	shared_ptr_entity make_smoke_sm() { return nullptr; }
	shared_ptr_entity make_smoke_med() { return nullptr; }
	shared_ptr_entity make_smoke_lg() { return nullptr; }
	shared_ptr_entity make_func_train_rotating() { return nullptr; }
	shared_ptr_entity make_func_subdoor_base() { return nullptr; }
	shared_ptr_entity make_func_subdoor_handle1() { return nullptr; }
	shared_ptr_entity make_func_subdoor_handle2() { return nullptr; }
	shared_ptr_entity make_props_trashcanA() { return nullptr; }
	shared_ptr_entity make_props_trashcan_fall() { return nullptr; }
	shared_ptr_entity make_props_hydrant() { return nullptr; }
	shared_ptr_entity make_props_antenna1a() { return nullptr; }
	shared_ptr_entity make_props_antenna1b() { return nullptr; }
	shared_ptr_entity make_props_antenna1c() { return nullptr; }
	shared_ptr_entity make_props_antenna2a() { return nullptr; }
	shared_ptr_entity make_props_antenna2b() { return nullptr; }
	shared_ptr_entity make_props_antenna2c() { return nullptr; }
	shared_ptr_entity make_props_antenna3a() { return nullptr; }
	shared_ptr_entity make_props_antenna3b() { return nullptr; }
	shared_ptr_entity make_props_antenna3c() { return nullptr; }
	shared_ptr_entity make_props_fan() { return nullptr; }
	shared_ptr_entity make_props_phone() { return nullptr; }
	shared_ptr_entity make_props_aircon() { return nullptr; }
	shared_ptr_entity make_props_tablesetA() { return nullptr; }
	shared_ptr_entity make_props_radio() { return nullptr; }
	shared_ptr_entity make_cast_buma() { return nullptr; }
	shared_ptr_entity make_cast_bumb() { return nullptr; }
	shared_ptr_entity make_elements_raincloud() { return nullptr; }
	shared_ptr_entity make_elements_snowcloud() { return nullptr; }
	shared_ptr_entity make_misc_cutscene_trigger() { return nullptr; }
	shared_ptr_entity make_misc_cutscene_camera() { return nullptr; }
	shared_ptr_entity make_trigger_unlock() { return nullptr; }
	shared_ptr_entity make_props_chair() { return nullptr; }
	shared_ptr_entity make_props_extinguisherA() { return nullptr; }
	shared_ptr_entity make_props_extinguisherB() { return nullptr; }
	shared_ptr_entity make_light_sconce() { return nullptr; }
	shared_ptr_entity make_props_motorcycle() { return nullptr; }
	shared_ptr_entity make_props_ammocrate_bust() { return nullptr; }
	shared_ptr_entity make_props_shelf() { return nullptr; }
	shared_ptr_entity make_props_mattressA() { return nullptr; }
	shared_ptr_entity make_props_mattressB() { return nullptr; }
	shared_ptr_entity make_props_mattressC() { return nullptr; }
	shared_ptr_entity make_trigger_motorcycle() { return nullptr; }
	shared_ptr_entity make_props_tv() { return nullptr; }
	shared_ptr_entity make_props_steam_machine() { return nullptr; }
	shared_ptr_entity make_light_bulb() { return nullptr; }
	shared_ptr_entity make_props_trash() { return nullptr; }
	shared_ptr_entity make_props_wall_fall() { return nullptr; }
	shared_ptr_entity make_props_trashbottle() { return nullptr; }
	shared_ptr_entity make_props_trashwall() { return nullptr; }
	shared_ptr_entity make_props_trashpaper() { return nullptr; }
	shared_ptr_entity make_props_trashcorner() { return nullptr; }
	shared_ptr_entity make_props_trashbottle_vert() { return nullptr; }
	shared_ptr_entity make_props_blimp() { return nullptr; }
	shared_ptr_entity make_misc_use_cutscene() { return nullptr; }
	shared_ptr_entity make_props_motorcycle_runaway() { return nullptr; }
	shared_ptr_entity make_trigger_hurt_fire() { return nullptr; }
	shared_ptr_entity make_props_shelf_fall() { return nullptr; }
	shared_ptr_entity make_target_fire() { return nullptr; }
	shared_ptr_entity make_props_rat() { return nullptr; }
	shared_ptr_entity make_props_rat_spawner() { return nullptr; }
	shared_ptr_entity make_props_rat_spawner_node() { return nullptr; }
	shared_ptr_entity make_target_flamethrower() { return nullptr; }
	shared_ptr_entity make_light_deco_sconce() { return nullptr; }
	shared_ptr_entity make_light_pendant() { return nullptr; }
	shared_ptr_entity make_props_shelfB_fall() { return nullptr; }
	shared_ptr_entity make_func_lift() { return nullptr; }
	shared_ptr_entity make_props_roof_vent() { return nullptr; }
	shared_ptr_entity make_props_rat_trigger() { return nullptr; }
	shared_ptr_entity make_props2_truck_die() { return nullptr; }
	shared_ptr_entity make_props_cola_machine() { return nullptr; }
	shared_ptr_entity make_props_cig_machine() { return nullptr; }
	shared_ptr_entity make_props2_barrels_fallA() { return nullptr; }
	shared_ptr_entity make_props2_barrels_fallB() { return nullptr; }
	shared_ptr_entity make_props2_clubcouch() { return nullptr; }
	shared_ptr_entity make_props2_clubchair() { return nullptr; }
	shared_ptr_entity make_props2_vaseA() { return nullptr; }
	shared_ptr_entity make_props2_vaseB() { return nullptr; }
	shared_ptr_entity make_props2_chair_conf() { return nullptr; }
	shared_ptr_entity make_props2_shelf_metal_A_fall() { return nullptr; }
	shared_ptr_entity make_props2_shelf_metal_B_fall() { return nullptr; }
	shared_ptr_entity make_props2_deadguy() { return nullptr; }
	shared_ptr_entity make_props2_chair_push() { return nullptr; }
	shared_ptr_entity make_props_crate_bust_32() { return nullptr; }
	shared_ptr_entity make_props_crate_bust_48() { return nullptr; }
	shared_ptr_entity make_props_crate_bust_64() { return nullptr; }
	shared_ptr_entity make_props2_flag() { return nullptr; }
	shared_ptr_entity make_props2_fish() { return nullptr; }
	shared_ptr_entity make_props2_fish_trigger() { return nullptr; }
	shared_ptr_entity make_props2_fish_spawner() { return nullptr; }
	shared_ptr_entity make_props2_fish_spawner_node() { return nullptr; }
	shared_ptr_entity make_props2_wall_fish() { return nullptr; }
	shared_ptr_entity make_props2_barrels_fall_ST() { return nullptr; }
	shared_ptr_entity make_props2_sign() { return nullptr; }
	shared_ptr_entity make_props2_lighthouse_beam() { return nullptr; }
	shared_ptr_entity make_props2_boat() { return nullptr; }
	shared_ptr_entity make_props2_buoy() { return nullptr; }
	shared_ptr_entity make_props2_buoy_side() { return nullptr; }
	shared_ptr_entity make_props2_deadguy_underwater() { return nullptr; }
	shared_ptr_entity make_props2_buoy_animate() { return nullptr; }
	shared_ptr_entity make_props2_gargoyle() { return nullptr; }
	shared_ptr_entity make_props2_clothesline() { return nullptr; }
	shared_ptr_entity make_props2_plant_XL() { return nullptr; }
	shared_ptr_entity make_props2_plant_SM() { return nullptr; }
	shared_ptr_entity make_props2_boatphone() { return nullptr; }
	shared_ptr_entity make_props2_ashtray() { return nullptr; }
	shared_ptr_entity make_props2_lunch() { return nullptr; }
	shared_ptr_entity make_props2_deadgal_headless() { return nullptr; }
	shared_ptr_entity make_props2_plant_bush() { return nullptr; }
	shared_ptr_entity make_props2_boat_animate() { return nullptr; }
	shared_ptr_entity make_props2_helicopter_animate() { return nullptr; }
	shared_ptr_entity make_props2_car_animate() { return nullptr; }
	shared_ptr_entity make_props2_car_topdown() { return nullptr; }
	shared_ptr_entity make_props2_car_topup() { return nullptr; }
	shared_ptr_entity make_props2_plant_fern() { return nullptr; }
	shared_ptr_entity make_props2_pinball_machine() { return nullptr; }
	shared_ptr_entity make_props2_barrels_PV_A() { return nullptr; }
	shared_ptr_entity make_props2_barrels_PV_C() { return nullptr; }
	shared_ptr_entity make_props2_barrels_PV_D() { return nullptr; }
	shared_ptr_entity make_props2_barrels_PV_E() { return nullptr; }
	shared_ptr_entity make_props2_barrels_PV_F() { return nullptr; }
	shared_ptr_entity make_light_chandelier() { return nullptr; }
	shared_ptr_entity make_props2_air_train() { return nullptr; }
	shared_ptr_entity make_props3_dead_louie() { return nullptr; }
	shared_ptr_entity make_props3_cut_boss_player_animate() { return nullptr; }
	shared_ptr_entity make_props3_deco_fixture() { return nullptr; }
	shared_ptr_entity make_props3_cut_boss_chick_animate() { return nullptr; }
	shared_ptr_entity make_props3_cut_train_run_animate() { return nullptr; }
	shared_ptr_entity make_props3_cut_A_animate() { return nullptr; }
	shared_ptr_entity make_props3_cut_B_animate() { return nullptr; }
	shared_ptr_entity make_props3_cut_C_animate() { return nullptr; }
	shared_ptr_entity make_props3_cut_D_animate() { return nullptr; }
	shared_ptr_entity make_props3_cash_counter_animate() { return nullptr; }
	shared_ptr_entity make_props2_barrels_PV_B() { return nullptr; }
	shared_ptr_entity make_props3_decanter() { return nullptr; }
	shared_ptr_entity make_props3_whiskey_glass() { return nullptr; }
	shared_ptr_entity make_props3_barrels_fall_nikki_A() { return nullptr; }
	shared_ptr_entity make_props3_barrels_fall_nikki_B() { return nullptr; }
	shared_ptr_entity make_props3_cut_run_to_car_animate() { return nullptr; }
	shared_ptr_entity make_props3_cut_final_animate() { return nullptr; }
	shared_ptr_entity make_props3_cash() { return nullptr; }
	shared_ptr_entity make_props3_cut_truck_driver() { return nullptr; }
	shared_ptr_entity make_props3_cut_pinball_guy_animate() { return nullptr; }
	shared_ptr_entity make_lightflare() { return nullptr; }
	shared_ptr_entity make_path_corner_cast() { return nullptr; }
	shared_ptr_entity make_pistol_mod_damage() { return nullptr; }
	shared_ptr_entity make_pistol_mod_rof() { return nullptr; }
	shared_ptr_entity make_pistol_mod_reload() { return nullptr; }
	shared_ptr_entity make_hmg_mod_cooling() { return nullptr; }
	shared_ptr_entity make_sfx_beacon() { return nullptr; }
	shared_ptr_entity make_refl() { return nullptr; }
	shared_ptr_entity make_dm_cashspawn() { return nullptr; }
	shared_ptr_entity make_dm_safebag() { return nullptr; }
	shared_ptr_entity make_dm_props_banner() { return nullptr; }

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
}
