#include <array>
#include <string>

namespace Freeking
{
	struct edict_t
	{
	};

	struct spawn_t
	{
		std::string name;
		void (*spawn)(edict_t* ent);
	};

	void SP_item_health(edict_t* self) {}
	void SP_item_health_small(edict_t* self) {}
	void SP_item_health_large(edict_t* self) {}
	void SP_item_health_mega(edict_t* self) {}
	void SP_info_player_start(edict_t* self) {}
	void SP_info_player_deathmatch(edict_t* self) {}
	void SP_info_player_coop(edict_t* self) {}
	void SP_info_player_intermission(edict_t* self) {}
	void SP_func_plat(edict_t* self) {}
	void SP_func_button(edict_t* self) {}
	void SP_func_door(edict_t* self) {}
	void SP_func_door_secret(edict_t* self) {}
	void SP_func_door_rotating(edict_t* self) {}
	void SP_func_rotating(edict_t* self) {}
	void SP_func_train(edict_t* self) {}
	void SP_func_water(edict_t* self) {}
	void SP_func_conveyor(edict_t* self) {}
	void SP_func_areaportal(edict_t* self) {}
	void SP_func_clock(edict_t* self) {}
	void SP_func_wall(edict_t* self) {}
	void SP_func_object(edict_t* self) {}
	void SP_func_timer(edict_t* self) {}
	void SP_func_explosive(edict_t* self) {}
	void SP_func_killbox(edict_t* self) {}
	void SP_func_object_repair(edict_t* self) {}
	void SP_rotating_light(edict_t* self) {}
	void SP_trigger_always(edict_t* self) {}
	void SP_trigger_once(edict_t* self) {}
	void SP_trigger_multiple(edict_t* self) {}
	void SP_trigger_relay(edict_t* self) {}
	void SP_trigger_push(edict_t* self) {}
	void SP_trigger_hurt(edict_t* self) {}
	void SP_trigger_key(edict_t* self) {}
	void SP_trigger_counter(edict_t* self) {}
	void SP_trigger_elevator(edict_t* self) {}
	void SP_trigger_gravity(edict_t* self) {}
	void SP_trigger_monsterjump(edict_t* self) {}
	void SP_target_temp_entity(edict_t* self) {}
	void SP_target_speaker(edict_t* self) {}
	void SP_target_explosion(edict_t* self) {}
	void SP_target_changelevel(edict_t* self) {}
	void SP_target_secret(edict_t* self) {}
	void SP_target_goal(edict_t* self) {}
	void SP_target_splash(edict_t* self) {}
	void SP_target_spawner(edict_t* self) {}
	void SP_target_blaster(edict_t* self) {}
	void SP_target_crosslevel_trigger(edict_t* self) {}
	void SP_target_crosslevel_target(edict_t* self) {}
	void SP_target_laser(edict_t* self) {}
	void SP_target_lightramp(edict_t* self) {}
	void SP_target_earthquake(edict_t* self) {}
	void SP_target_character(edict_t* self) {}
	void SP_target_string(edict_t* self) {}
	void SP_target_mal_laser(edict_t* self) {}
	void SP_worldspawn(edict_t* self) {}
	void SP_viewthing(edict_t* self) {}
	void SP_light(edict_t* self) {}
	void SP_light_mine1(edict_t* self) {}
	void SP_light_mine2(edict_t* self) {}
	void SP_info_null(edict_t* self) {}
	void SP_func_group(edict_t* self) {}
	void SP_info_notnull(edict_t* self) {}
	void SP_path_corner(edict_t* self) {}
	void SP_junior(edict_t* self) {}
	void SP_misc_explobox(edict_t* self) {}
	void SP_misc_gib_arm(edict_t* self) {}
	void SP_misc_gib_leg(edict_t* self) {}
	void SP_misc_gib_head(edict_t* self) {}
	void SP_misc_teleporter(edict_t* self) {}
	void SP_misc_teleporter_dest(edict_t* self) {}
	void SP_misc_amb4(edict_t* self) {}
	void SP_cast_punk(edict_t* self) {}
	void SP_cast_thug(edict_t* self) {}
	void SP_cast_thug_sit(edict_t* self) {}
	void SP_cast_bitch(edict_t* self) {}
	void SP_cast_dog(edict_t* self) {}
	void SP_cast_runt(edict_t* self) {}
	void SP_cast_bum_sit(edict_t* self) {}
	void SP_cast_shorty(edict_t* self) {}
	void SP_cast_whore(edict_t* self) {}
	void SP_cast_punk_window(edict_t* self) {}
	void SP_cast_punk2(edict_t* self) {}
	void SP_cast_rosie(edict_t* self) {}
	void SP_ai_boundary(edict_t* self) {}
	void SP_ai_event_hostile(edict_t* self) {}
	void SP_ai_event_follow(edict_t* self) {}
	void SP_ai_guard(edict_t* self) {}
	void SP_ai_territory(edict_t* self) {}
	void SP_ai_trigger_character(edict_t* self) {}
	void SP_ai_locked_door(edict_t* self) {}
	void SP_misc_skidrow_radio(edict_t* self) {}
	void SP_misc_skidrow_ambush(edict_t* self) {}
	void SP_misc_skidrow_radio_repeater(edict_t* self) {}
	void SP_ai_ty_fuseblown(edict_t* self) {}
	void SP_ai_moker_notinoffice(edict_t* self) {}
	void SP_misc_grunt(edict_t* self) {}
	void SP_misc_fidelA(edict_t* self) {}
	void SP_misc_car(edict_t* self) {}
	void SP_misc_smoke(edict_t* self) {}
	void SP_elps(edict_t* self) {}
	void SP_misc_alarm(edict_t* self) {}
	void SP_trigger_hurt_electric(edict_t* self) {}
	void SP_pawn_o_matic(edict_t* self) {}
	void SP_ai_safespot(edict_t* self) {}
	void SP_misc_skidrow_ai_reset(edict_t* self) {}
	void SP_ai_combat_spot(edict_t* self) {}
	void SP_misc_skidrow_afraid(edict_t* self) {}
	void SP_misc_steeltown_afraid(edict_t* self) {}
	void SP_misc_kroker_afraid(edict_t* self) {}
	void SP_rc_initiation_observer(edict_t* self) {}
	void SP_rc_initiation_brush(edict_t* self) {}
	void SP_misc_pv_afraid(edict_t* self) {}
	void SP_misc_ty_afraid(edict_t* self) {}
	void SP_ai_ty_mo_boundry(edict_t* self) {}
	void SP_ai_sy_dykes_boundry(edict_t* self) {}
	void SP_misc_sy_afraid(edict_t* self) {}
	void SP_ep_skidrow_flag(edict_t* self) {}
	void SP_ai_sy_oilcan(edict_t* self) {}
	void SP_ai_ty_valvehandle(edict_t* self) {}
	void SP_ai_pv_fuseblown1(edict_t* self) {}
	void SP_ai_pv_fuseblown2(edict_t* self) {}
	void SP_ai_pv_deadlouie(edict_t* self) {}
	void SP_ai_sy_blefty(edict_t* self) {}
	void SP_misc_barry_bitch(edict_t* self) {}
	void SP_misc_corky_fidel_mdx_pcx(edict_t* self) {}
	void SP_misc_corky_fidel_mdx_tga(edict_t* self) {}
	void SP_misc_cut_scene(edict_t* self) {}
	void SP_light_fire_esm(edict_t* self) {}
	void SP_light_fire_sm(edict_t* self) {}
	void SP_light_fire_med(edict_t* self) {}
	void SP_light_fire_lg(edict_t* self) {}
	void SP_smoke_esm(edict_t* self) {}
	void SP_smoke_sm(edict_t* self) {}
	void SP_smoke_med(edict_t* self) {}
	void SP_smoke_lg(edict_t* self) {}
	void SP_func_train_rotating(edict_t* self) {}
	void SP_func_subdoor_base(edict_t* self) {}
	void SP_func_subdoor_handle1(edict_t* self) {}
	void SP_func_subdoor_handle2(edict_t* self) {}
	void SP_props_trashcanA(edict_t* self) {}
	void SP_props_trashcan_fall(edict_t* self) {}
	void SP_props_hydrant(edict_t* self) {}
	void SP_props_antenna1a(edict_t* self) {}
	void SP_props_antenna1b(edict_t* self) {}
	void SP_props_antenna1c(edict_t* self) {}
	void SP_props_antenna2a(edict_t* self) {}
	void SP_props_antenna2b(edict_t* self) {}
	void SP_props_antenna2c(edict_t* self) {}
	void SP_props_antenna3a(edict_t* self) {}
	void SP_props_antenna3b(edict_t* self) {}
	void SP_props_antenna3c(edict_t* self) {}
	void SP_props_fan(edict_t* self) {}
	void SP_props_phone(edict_t* self) {}
	void SP_props_aircon(edict_t* self) {}
	void SP_props_tablesetA(edict_t* self) {}
	void SP_props_radio(edict_t* self) {}
	void SP_cast_buma(edict_t* self) {}
	void SP_cast_bumb(edict_t* self) {}
	void SP_elements_raincloud(edict_t* self) {}
	void SP_elements_snowcloud(edict_t* self) {}
	void SP_misc_cutscene_trigger(edict_t* self) {}
	void SP_misc_cutscene_camera(edict_t* self) {}
	void SP_trigger_unlock(edict_t* self) {}
	void SP_props_chair(edict_t* self) {}
	void SP_props_extinguisherA(edict_t* self) {}
	void SP_props_extinguisherB(edict_t* self) {}
	void SP_light_sconce(edict_t* self) {}
	void SP_props_motorcycle(edict_t* self) {}
	void SP_props_ammocrate_bust(edict_t* self) {}
	void SP_props_shelf(edict_t* self) {}
	void SP_props_mattressA(edict_t* self) {}
	void SP_props_mattressB(edict_t* self) {}
	void SP_props_mattressC(edict_t* self) {}
	void SP_trigger_motorcycle(edict_t* self) {}
	void SP_props_tv(edict_t* self) {}
	void SP_props_steam_machine(edict_t* self) {}
	void SP_light_bulb(edict_t* self) {}
	void SP_props_trash(edict_t* self) {}
	void SP_props_wall_fall(edict_t* self) {}
	void SP_props_trashbottle(edict_t* self) {}
	void SP_props_trashwall(edict_t* self) {}
	void SP_props_trashpaper(edict_t* self) {}
	void SP_props_trashcorner(edict_t* self) {}
	void SP_props_trashbottle_vert(edict_t* self) {}
	void SP_props_blimp(edict_t* self) {}
	void SP_misc_use_cutscene(edict_t* self) {}
	void SP_props_motorcycle_runaway(edict_t* self) {}
	void SP_trigger_hurt_fire(edict_t* self) {}
	void SP_props_shelf_fall(edict_t* self) {}
	void SP_target_fire(edict_t* self) {}
	void SP_props_rat(edict_t* self) {}
	void SP_props_rat_spawner(edict_t* self) {}
	void SP_props_rat_spawner_node(edict_t* self) {}
	void SP_target_flamethrower(edict_t* self) {}
	void SP_light_deco_sconce(edict_t* self) {}
	void SP_light_pendant(edict_t* self) {}
	void SP_props_shelfB_fall(edict_t* self) {}
	void SP_func_lift(edict_t* self) {}
	void SP_props_roof_vent(edict_t* self) {}
	void SP_props_rat_trigger(edict_t* self) {}
	void SP_props2_truck_die(edict_t* self) {}
	void SP_props_cola_machine(edict_t* self) {}
	void SP_props_cig_machine(edict_t* self) {}
	void SP_props2_barrels_fallA(edict_t* self) {}
	void SP_props2_barrels_fallB(edict_t* self) {}
	void SP_props2_clubcouch(edict_t* self) {}
	void SP_props2_clubchair(edict_t* self) {}
	void SP_props2_vaseA(edict_t* self) {}
	void SP_props2_vaseB(edict_t* self) {}
	void SP_props2_chair_conf(edict_t* self) {}
	void SP_props2_shelf_metal_A_fall(edict_t* self) {}
	void SP_props2_shelf_metal_B_fall(edict_t* self) {}
	void SP_props2_deadguy(edict_t* self) {}
	void SP_props2_chair_push(edict_t* self) {}
	void SP_props_crate_bust_32(edict_t* self) {}
	void SP_props_crate_bust_48(edict_t* self) {}
	void SP_props_crate_bust_64(edict_t* self) {}
	void SP_props2_flag(edict_t* self) {}
	void SP_props2_fish(edict_t* self) {}
	void SP_props2_fish_trigger(edict_t* self) {}
	void SP_props2_fish_spawner(edict_t* self) {}
	void SP_props2_fish_spawner_node(edict_t* self) {}
	void SP_props2_wall_fish(edict_t* self) {}
	void SP_props2_barrels_fall_ST(edict_t* self) {}
	void SP_props2_sign(edict_t* self) {}
	void SP_props2_lighthouse_beam(edict_t* self) {}
	void SP_props2_boat(edict_t* self) {}
	void SP_props2_buoy(edict_t* self) {}
	void SP_props2_buoy_side(edict_t* self) {}
	void SP_props2_deadguy_underwater(edict_t* self) {}
	void SP_props2_buoy_animate(edict_t* self) {}
	void SP_props2_gargoyle(edict_t* self) {}
	void SP_props2_clothesline(edict_t* self) {}
	void SP_props2_plant_XL(edict_t* self) {}
	void SP_props2_plant_SM(edict_t* self) {}
	void SP_props2_boatphone(edict_t* self) {}
	void SP_props2_ashtray(edict_t* self) {}
	void SP_props2_lunch(edict_t* self) {}
	void SP_props2_deadgal_headless(edict_t* self) {}
	void SP_props2_plant_bush(edict_t* self) {}
	void SP_props2_boat_animate(edict_t* self) {}
	void SP_props2_helicopter_animate(edict_t* self) {}
	void SP_props2_car_animate(edict_t* self) {}
	void SP_props2_car_topdown(edict_t* self) {}
	void SP_props2_car_topup(edict_t* self) {}
	void SP_props2_plant_fern(edict_t* self) {}
	void SP_props2_pinball_machine(edict_t* self) {}
	void SP_props2_barrels_PV_A(edict_t* self) {}
	void SP_props2_barrels_PV_C(edict_t* self) {}
	void SP_props2_barrels_PV_D(edict_t* self) {}
	void SP_props2_barrels_PV_E(edict_t* self) {}
	void SP_props2_barrels_PV_F(edict_t* self) {}
	void SP_light_chandelier(edict_t* self) {}
	void SP_props2_air_train(edict_t* self) {}
	void SP_props3_dead_louie(edict_t* self) {}
	void SP_props3_cut_boss_player_animate(edict_t* self) {}
	void SP_props3_deco_fixture(edict_t* self) {}
	void SP_props3_cut_boss_chick_animate(edict_t* self) {}
	void SP_props3_cut_train_run_animate(edict_t* self) {}
	void SP_props3_cut_A_animate(edict_t* self) {}
	void SP_props3_cut_B_animate(edict_t* self) {}
	void SP_props3_cut_C_animate(edict_t* self) {}
	void SP_props3_cut_D_animate(edict_t* self) {}
	void SP_props3_cash_counter_animate(edict_t* self) {}
	void SP_props2_barrels_PV_B(edict_t* self) {}
	void SP_props3_decanter(edict_t* self) {}
	void SP_props3_whiskey_glass(edict_t* self) {}
	void SP_props3_barrels_fall_nikki_A(edict_t* self) {}
	void SP_props3_barrels_fall_nikki_B(edict_t* self) {}
	void SP_props3_cut_run_to_car_animate(edict_t* self) {}
	void SP_props3_cut_final_animate(edict_t* self) {}
	void SP_props3_cash(edict_t* self) {}
	void SP_props3_cut_truck_driver(edict_t* self) {}
	void SP_props3_cut_pinball_guy_animate(edict_t* self) {}
	void SP_lightflare(edict_t* self) {}
	void SP_path_corner_cast(edict_t* self) {}
	void SP_pistol_mod_damage(edict_t* self) {}
	void SP_pistol_mod_rof(edict_t* self) {}
	void SP_pistol_mod_reload(edict_t* self) {}
	void SP_hmg_mod_cooling(edict_t* self) {}
	void SP_sfx_beacon(edict_t* self) {}
	void SP_refl(edict_t* self) {}
	void SP_dm_cashspawn(edict_t* self) {}
	void SP_dm_safebag(edict_t* self) {}
	void SP_dm_props_banner(edict_t* self) {}

	std::array<spawn_t, 285> spawns =
	{{
		{"item_health", SP_item_health},
		{"item_health_small", SP_item_health_small},
		{"item_health_large", SP_item_health_large},
		{"item_health_mega", SP_item_health_mega},
		{"info_player_start", SP_info_player_start},
		{"info_player_deathmatch", SP_info_player_deathmatch},
		{"info_player_coop", SP_info_player_coop},
		{"info_player_intermission", SP_info_player_intermission},
		{"func_plat", SP_func_plat},
		{"func_button", SP_func_button},
		{"func_door", SP_func_door},
		{"func_door_secret", SP_func_door_secret},
		{"func_door_rotating", SP_func_door_rotating},
		{"func_rotating", SP_func_rotating},
		{"func_train", SP_func_train},
		{"func_water", SP_func_water},
		{"func_conveyor", SP_func_conveyor},
		{"func_areaportal", SP_func_areaportal},
		{"func_clock", SP_func_clock},
		{"func_wall", SP_func_wall},
		{"func_object", SP_func_object},
		{"func_timer", SP_func_timer},
		{"func_explosive", SP_func_explosive},
		{"func_killbox", SP_func_killbox},
		{"func_object_repair", SP_func_object_repair},
		{"rotating_light", SP_rotating_light},
		{"trigger_always", SP_trigger_always},
		{"trigger_once", SP_trigger_once},
		{"trigger_multiple", SP_trigger_multiple},
		{"trigger_relay", SP_trigger_relay},
		{"trigger_push", SP_trigger_push},
		{"trigger_hurt", SP_trigger_hurt},
		{"trigger_key", SP_trigger_key},
		{"trigger_counter", SP_trigger_counter},
		{"trigger_elevator", SP_trigger_elevator},
		{"trigger_gravity", SP_trigger_gravity},
		{"trigger_monsterjump", SP_trigger_monsterjump},
		{"target_temp_entity", SP_target_temp_entity},
		{"target_speaker", SP_target_speaker},
		{"target_explosion", SP_target_explosion},
		{"target_changelevel", SP_target_changelevel},
		{"target_secret", SP_target_secret},
		{"target_goal", SP_target_goal},
		{"target_splash", SP_target_splash},
		{"target_spawner", SP_target_spawner},
		{"target_blaster", SP_target_blaster},
		{"target_crosslevel_trigger", SP_target_crosslevel_trigger},
		{"target_crosslevel_target", SP_target_crosslevel_target},
		{"target_laser", SP_target_laser},
		{"target_lightramp", SP_target_lightramp},
		{"target_earthquake", SP_target_earthquake},
		{"target_character", SP_target_character},
		{"target_string", SP_target_string},
		{"target_mal_laser", SP_target_mal_laser},
		{"worldspawn", SP_worldspawn},
		{"viewthing", SP_viewthing},
		{"light", SP_light},
		{"light_mine1", SP_light_mine1},
		{"light_mine2", SP_light_mine2},
		{"info_null", SP_info_null},
		{"func_group", SP_func_group},
		{"info_notnull", SP_info_notnull},
		{"path_corner", SP_path_corner},
		{"junior", SP_junior},
		{"misc_explobox", SP_misc_explobox},
		{"misc_gib_arm", SP_misc_gib_arm},
		{"misc_gib_leg", SP_misc_gib_leg},
		{"misc_gib_head", SP_misc_gib_head},
		{"misc_teleporter", SP_misc_teleporter},
		{"misc_teleporter_dest", SP_misc_teleporter_dest},
		{"misc_amb4", SP_misc_amb4},
		{"cast_punk", SP_cast_punk},
		{"cast_thug", SP_cast_thug},
		{"cast_thug_sit", SP_cast_thug_sit},
		{"cast_bitch", SP_cast_bitch},
		{"cast_dog", SP_cast_dog},
		{"cast_runt", SP_cast_runt},
		{"cast_bum_sit", SP_cast_bum_sit},
		{"cast_shorty", SP_cast_shorty},
		{"cast_whore", SP_cast_whore},
		{"cast_punk_window", SP_cast_punk_window},
		{"cast_punk2", SP_cast_punk2},
		{"cast_rosie", SP_cast_rosie},
		{"ai_boundary", SP_ai_boundary},
		{"ai_event_hostile", SP_ai_event_hostile},
		{"ai_event_follow", SP_ai_event_follow},
		{"ai_guard", SP_ai_guard},
		{"ai_territory", SP_ai_territory},
		{"ai_trigger_character", SP_ai_trigger_character},
		{"ai_locked_door", SP_ai_locked_door},
		{"misc_skidrow_radio", SP_misc_skidrow_radio},
		{"misc_skidrow_ambush", SP_misc_skidrow_ambush},
		{"misc_skidrow_radio_repeater", SP_misc_skidrow_radio_repeater},
		{"ai_ty_fuseblown", SP_ai_ty_fuseblown},
		{"ai_moker_notinoffice", SP_ai_moker_notinoffice},
		{"misc_grunt", SP_misc_grunt},
		{"misc_fidelA", SP_misc_fidelA},
		{"misc_car", SP_misc_car},
		{"misc_smoke", SP_misc_smoke},
		{"elps", SP_elps},
		{"misc_alarm", SP_misc_alarm},
		{"trigger_hurt_electric", SP_trigger_hurt_electric},
		{"pawn_o_matic", SP_pawn_o_matic},
		{"ai_safespot", SP_ai_safespot},
		{"misc_skidrow_ai_reset", SP_misc_skidrow_ai_reset},
		{"ai_combat_spot", SP_ai_combat_spot},
		{"misc_skidrow_afraid", SP_misc_skidrow_afraid},
		{"misc_steeltown_afraid", SP_misc_steeltown_afraid},
		{"misc_kroker_afraid", SP_misc_kroker_afraid},
		{"rc_initiation_observer", SP_rc_initiation_observer},
		{"rc_initiation_brush", SP_rc_initiation_brush},
		{"misc_pv_afraid", SP_misc_pv_afraid},
		{"misc_ty_afraid", SP_misc_ty_afraid},
		{"ai_ty_mo_boundry", SP_ai_ty_mo_boundry},
		{"ai_sy_dykes_boundry", SP_ai_sy_dykes_boundry},
		{"misc_sy_afraid", SP_misc_sy_afraid},
		{"ep_skidrow_flag", SP_ep_skidrow_flag},
		{"ai_sy_oilcan", SP_ai_sy_oilcan},
		{"ai_ty_valvehandle", SP_ai_ty_valvehandle},
		{"ai_pv_fuseblown1", SP_ai_pv_fuseblown1},
		{"ai_pv_fuseblown2", SP_ai_pv_fuseblown2},
		{"ai_pv_deadlouie", SP_ai_pv_deadlouie},
		{"ai_sy_blefty", SP_ai_sy_blefty},
		{"misc_barry_bitch", SP_misc_barry_bitch},
		{"misc_corky_fidel_mdx_pcx", SP_misc_corky_fidel_mdx_pcx},
		{"misc_corky_fidel_mdx_tga", SP_misc_corky_fidel_mdx_tga},
		{"misc_cut_scene", SP_misc_cut_scene},
		{"light_fire_esm", SP_light_fire_esm},
		{"light_fire_sm", SP_light_fire_sm},
		{"light_fire_med", SP_light_fire_med},
		{"light_fire_lg", SP_light_fire_lg},
		{"smoke_esm", SP_smoke_esm},
		{"smoke_sm", SP_smoke_sm},
		{"smoke_med", SP_smoke_med},
		{"smoke_lg", SP_smoke_lg},
		{"func_train_rotating", SP_func_train_rotating},
		{"func_subdoor_base", SP_func_subdoor_base},
		{"func_subdoor_handle1", SP_func_subdoor_handle1},
		{"func_subdoor_handle2", SP_func_subdoor_handle2},
		{"props_trashcanA", SP_props_trashcanA},
		{"props_trashcan_fall", SP_props_trashcan_fall},
		{"props_hydrant", SP_props_hydrant},
		{"props_antenna1a", SP_props_antenna1a},
		{"props_antenna1b", SP_props_antenna1b},
		{"props_antenna1c", SP_props_antenna1c},
		{"props_antenna2a", SP_props_antenna2a},
		{"props_antenna2b", SP_props_antenna2b},
		{"props_antenna2c", SP_props_antenna2c},
		{"props_antenna3a", SP_props_antenna3a},
		{"props_antenna3b", SP_props_antenna3b},
		{"props_antenna3c", SP_props_antenna3c},
		{"props_fan", SP_props_fan},
		{"props_phone", SP_props_phone},
		{"props_aircon", SP_props_aircon},
		{"props_tablesetA", SP_props_tablesetA},
		{"props_radio", SP_props_radio},
		{"cast_buma", SP_cast_buma},
		{"cast_bumb", SP_cast_bumb},
		{"elements_raincloud", SP_elements_raincloud},
		{"elements_snowcloud", SP_elements_snowcloud},
		{"misc_cutscene_trigger", SP_misc_cutscene_trigger},
		{"misc_cutscene_camera", SP_misc_cutscene_camera},
		{"trigger_unlock", SP_trigger_unlock},
		{"props_chair", SP_props_chair},
		{"props_extinguisherA", SP_props_extinguisherA},
		{"props_extinguisherB", SP_props_extinguisherB},
		{"light_sconce", SP_light_sconce},
		{"props_motorcycle", SP_props_motorcycle},
		{"props_ammocrate_bust", SP_props_ammocrate_bust},
		{"props_shelf", SP_props_shelf},
		{"props_mattressA", SP_props_mattressA},
		{"props_mattressB", SP_props_mattressB},
		{"props_mattressC", SP_props_mattressC},
		{"trigger_motorcycle", SP_trigger_motorcycle},
		{"props_tv", SP_props_tv},
		{"props_steam_machine", SP_props_steam_machine},
		{"light_bulb", SP_light_bulb},
		{"props_trash", SP_props_trash},
		{"props_wall_fall", SP_props_wall_fall},
		{"props_trashbottle", SP_props_trashbottle},
		{"props_trashwall", SP_props_trashwall},
		{"props_trashpaper", SP_props_trashpaper},
		{"props_trashcorner", SP_props_trashcorner},
		{"props_trashbottle_vert", SP_props_trashbottle_vert},
		{"props_blimp", SP_props_blimp},
		{"misc_use_cutscene", SP_misc_use_cutscene},
		{"props_motorcycle_runaway", SP_props_motorcycle_runaway},
		{"trigger_hurt_fire", SP_trigger_hurt_fire},
		{"props_shelf_fall", SP_props_shelf_fall},
		{"target_fire", SP_target_fire},
		{"props_rat", SP_props_rat},
		{"props_rat_spawner", SP_props_rat_spawner},
		{"props_rat_spawner_node", SP_props_rat_spawner_node},
		{"target_flamethrower", SP_target_flamethrower},
		{"light_deco_sconce", SP_light_deco_sconce},
		{"light_pendant", SP_light_pendant},
		{"props_shelfB_fall", SP_props_shelfB_fall},
		{"func_lift", SP_func_lift},
		{"props_roof_vent", SP_props_roof_vent},
		{"props_rat_trigger", SP_props_rat_trigger},
		{"props2_truck_die", SP_props2_truck_die},
		{"props_cola_machine", SP_props_cola_machine},
		{"props_cig_machine", SP_props_cig_machine},
		{"props2_barrels_fallA", SP_props2_barrels_fallA},
		{"props2_barrels_fallB", SP_props2_barrels_fallB},
		{"props2_clubcouch", SP_props2_clubcouch},
		{"props2_clubchair", SP_props2_clubchair},
		{"props2_vaseA", SP_props2_vaseA},
		{"props2_vaseB", SP_props2_vaseB},
		{"props2_chair_conf", SP_props2_chair_conf},
		{"props2_shelf_metal_A_fall", SP_props2_shelf_metal_A_fall},
		{"props2_shelf_metal_B_fall", SP_props2_shelf_metal_B_fall},
		{"props2_deadguy", SP_props2_deadguy},
		{"props2_chair_push", SP_props2_chair_push},
		{"props_crate_bust_32", SP_props_crate_bust_32},
		{"props_crate_bust_48", SP_props_crate_bust_48},
		{"props_crate_bust_64", SP_props_crate_bust_64},
		{"props2_flag", SP_props2_flag},
		{"props2_fish", SP_props2_fish},
		{"props2_fish_trigger", SP_props2_fish_trigger},
		{"props2_fish_spawner", SP_props2_fish_spawner},
		{"props2_fish_spawner_node", SP_props2_fish_spawner_node},
		{"props2_wall_fish", SP_props2_wall_fish},
		{"props2_barrels_fall_ST", SP_props2_barrels_fall_ST},
		{"props2_sign", SP_props2_sign},
		{"props2_lighthouse_beam", SP_props2_lighthouse_beam},
		{"props2_boat", SP_props2_boat},
		{"props2_buoy", SP_props2_buoy},
		{"props2_buoy_side", SP_props2_buoy_side},
		{"props2_deadguy_underwater", SP_props2_deadguy_underwater},
		{"props2_buoy_animate", SP_props2_buoy_animate},
		{"props2_gargoyle", SP_props2_gargoyle},
		{"props2_clothesline", SP_props2_clothesline},
		{"props2_plant_XL", SP_props2_plant_XL},
		{"props2_plant_SM", SP_props2_plant_SM},
		{"props2_boatphone", SP_props2_boatphone},
		{"props2_ashtray", SP_props2_ashtray},
		{"props2_lunch", SP_props2_lunch},
		{"props2_deadgal_headless", SP_props2_deadgal_headless},
		{"props2_plant_bush", SP_props2_plant_bush},
		{"props2_boat_animate", SP_props2_boat_animate},
		{"props2_helicopter_animate", SP_props2_helicopter_animate},
		{"props2_car_animate", SP_props2_car_animate},
		{"props2_car_topdown", SP_props2_car_topdown},
		{"props2_car_topup", SP_props2_car_topup},
		{"props2_plant_fern", SP_props2_plant_fern},
		{"props2_pinball_machine", SP_props2_pinball_machine},
		{"props2_barrels_PV_A", SP_props2_barrels_PV_A},
		{"props2_barrels_PV_C", SP_props2_barrels_PV_C},
		{"props2_barrels_PV_D", SP_props2_barrels_PV_D},
		{"props2_barrels_PV_E", SP_props2_barrels_PV_E},
		{"props2_barrels_PV_F", SP_props2_barrels_PV_F},
		{"light_chandelier", SP_light_chandelier},
		{"props2_air_train", SP_props2_air_train},
		{"props3_dead_louie", SP_props3_dead_louie},
		{"props3_cut_boss_player_animate", SP_props3_cut_boss_player_animate},
		{"props3_deco_fixture", SP_props3_deco_fixture},
		{"props3_cut_boss_chick_animate", SP_props3_cut_boss_chick_animate},
		{"props3_cut_train_run_animate", SP_props3_cut_train_run_animate},
		{"props3_cut_A_animate", SP_props3_cut_A_animate},
		{"props3_cut_B_animate", SP_props3_cut_B_animate},
		{"props3_cut_C_animate", SP_props3_cut_C_animate},
		{"props3_cut_D_animate", SP_props3_cut_D_animate},
		{"props3_cash_counter_animate", SP_props3_cash_counter_animate},
		{"props2_barrels_PV_B", SP_props2_barrels_PV_B},
		{"props3_decanter", SP_props3_decanter},
		{"props3_whiskey_glass", SP_props3_whiskey_glass},
		{"props3_barrels_fall_nikki_A", SP_props3_barrels_fall_nikki_A},
		{"props3_barrels_fall_nikki_B", SP_props3_barrels_fall_nikki_B},
		{"props3_cut_run_to_car_animate", SP_props3_cut_run_to_car_animate},
		{"props3_cut_final_animate", SP_props3_cut_final_animate},
		{"props3_cash", SP_props3_cash},
		{"props3_cut_truck_driver", SP_props3_cut_truck_driver},
		{"props3_cut_pinball_guy_animate", SP_props3_cut_pinball_guy_animate},
		{"lightflare", SP_lightflare},
		{"path_corner_cast", SP_path_corner_cast},
		{"pistol_mod_damage", SP_pistol_mod_damage},
		{"pistol_mod_rof", SP_pistol_mod_rof},
		{"pistol_mod_reload", SP_pistol_mod_reload},
		{"hmg_mod_cooling", SP_hmg_mod_cooling},
		{"sfx_beacon", SP_sfx_beacon},
		{"refl", SP_refl},
		{"dm_cashspawn", SP_dm_cashspawn},
		{"dm_safebag", SP_dm_safebag},
		{"dm_props_banner", SP_dm_props_banner}
	}};
}
