#pragma once
#include <cstdint>
#include <windows.h>
#include "network_session_parameter_session.h"
#include "network_session_parameters_game.h"
#include "network_session_parameters_game_variant.h"
#include "network_session_parameters_map_variant.h"
#include "network_session_parameter_saved_film.h"
#include "network_session_parameters_matchmaking.h"
#include "network_session_parameter_types.h"
#include "network_session_parameters_ui.h"
#include "..\messages\network_message_type_collection.h"

#pragma pack(push, 4)
class c_network_session;
class c_network_observer;
class c_network_session_parameters
{
public:
	void check_to_send_updates();
	void check_to_send_change_requests();
	void update();
	bool handle_change_request(bool is_leader, s_network_message_parameters_request const* message);

	c_network_session_parameter_session_mode session_mode;
	c_network_session_parameter_session_size session_size;
	c_generic_network_session_parameter_privacy_mode privacy_mode;
	c_network_session_parameter_ui_game_mode ui_game_mode;
	c_generic_network_session_parameter_dedicated_server_session_state dedicated_server_session_state;
	c_network_session_parameter_map map;
	c_network_session_parameter_initial_participants initial_participants;
	c_generic_network_session_parameter_qword game_instance;
	c_generic_network_session_parameter_ulong random_seed;
	c_generic_network_session_parameter_ulong language;
	c_generic_network_session_parameter_long determinism_version;
	c_network_session_parameter_game_simulation_protocol game_simulation_protocol;
	c_generic_network_session_parameter_ulong campaign_difficulty;
	c_generic_network_session_parameter_ulong campaign_active_skulls_primary;
	c_generic_network_session_parameter_ulong campaign_active_skulls_secondary;
	c_generic_network_session_parameter_short campaign_metagame_scoring;
	c_generic_network_session_parameter_short campaign_insertion_point;
	c_generic_network_session_parameter_uchar ui_state;
	c_generic_network_session_parameter_bool end_game;
	c_generic_network_session_parameter_start_mode start_mode;
	c_network_session_parameter_game_variant game_variant;
	c_network_session_parameter_map_variant map_variant;
	c_generic_network_session_parameter_saved_film_description saved_film;
	c_network_session_parameter_saved_film_game_options saved_film_game_options;
	c_network_session_parameter_game_start_status game_start_status;
	c_network_session_parameter_countdown_timer countdown_timer;
	c_network_session_parameter_voice_repeater voice_repeater;
	c_network_session_parameter_requested_remote_join_data requested_remote_join_data;
	c_network_session_parameter_remote_join_data remote_join_data;
	c_network_session_parameter_synchronous_out_of_sync synchronous_out_of_sync;
	c_network_session_parameter_matchmaking_messaging matchmaking_messaging;
	c_generic_network_session_parameter_ulong host_frame_quality;
	c_network_session_parameter_request_campaign_quit request_campaign_quit;
	c_network_session_parameter_leader_properties leader_properties;
	c_network_session_parameter_lobby_vote_set lobby_vote_set;
	long : 32;
	c_network_session* session;
	c_network_observer* observer;
	c_network_session_parameter_base* parameters[k_network_session_parameter_type_count];
	uint32_t flags;
	uint32_t initial_parameters_update_mask;
};
static_assert(sizeof(c_network_session_parameters) == 0xCA114);
#pragma pack(pop)