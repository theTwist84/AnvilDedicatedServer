#include "network_session_membership.h"
#include "..\..\dllmain.h"
#include "..\network_globals.h"
#include <iostream>
#include "..\network_utilities.h"
#include "network_session.h"
#include "network_managed_session.h"

long c_network_session_membership::get_first_peer()
{
    typedef long(__fastcall* get_first_peer_ptr)(c_network_session_membership* session_membership);
    auto get_first_peer = reinterpret_cast<get_first_peer_ptr>(module_base + 0x313F0);
    return get_first_peer(this);
}

long c_network_session_membership::get_next_peer(long peer_index)
{
    long next_index = peer_index + 1;
    if (next_index >= k_network_maximum_machines_per_session)
        return -1;
    while (true)
    {
        if (_bittest((long*)&this->m_baseline.valid_peer_mask, next_index))
            break;
        if (++next_index >= k_network_maximum_machines_per_session)
            return -1;
    }
    return next_index;
}

long c_network_session_membership::get_peer_from_secure_address(s_transport_secure_address const* secure_address)
{
    typedef long(__thiscall* get_peer_from_secure_address_ptr)(c_network_session_membership* session_membership, s_transport_secure_address const* secure_address);
    auto get_peer_from_secure_address = reinterpret_cast<get_peer_from_secure_address_ptr>(module_base + 0x312B0);
    return get_peer_from_secure_address(this, secure_address);
}

bool c_network_session_membership::is_peer_valid(long peer_index)
{
    return (m_baseline.valid_peer_mask >> peer_index) & 1;
}

bool c_network_session_membership::add_peer(long peer_index, e_network_session_peer_state peer_state, uint32_t joining_network_version_number, s_transport_secure_address const* secure_address, uint64_t join_party_nonce, uint64_t join_nonce)
{
    typedef long(__thiscall* add_peer_ptr)(c_network_session_membership* session_membership, long peer_index, e_network_session_peer_state peer_state, uint32_t joining_network_version_number, s_transport_secure_address const* secure_address, uint64_t join_party_nonce, uint64_t join_nonce);
    auto add_peer_call = reinterpret_cast<add_peer_ptr>(module_base + 0x30DE0);
    return add_peer_call(this, peer_index, peer_state, joining_network_version_number, secure_address, join_party_nonce, join_nonce);
}

long c_network_session_membership::find_or_add_player(long peer_index, s_player_identifier const* player_identifier, bool join_from_recruiting)
{
    typedef long(__thiscall* find_or_add_player_ptr)(c_network_session_membership* session_membership, long peer_index, s_player_identifier const* player_identifier, bool join_from_recruiting);
    auto find_or_add_player_call = reinterpret_cast<find_or_add_player_ptr>(module_base + 0x31950);
    return find_or_add_player_call(this, peer_index, player_identifier, join_from_recruiting);
}

void c_network_session_membership::update_player_data(long player_index, s_player_configuration const* player_config)
{
    memmove(&this->m_baseline.players[player_index].configuration, player_config, sizeof(s_player_configuration));
    this->increment_update();
}

long c_network_session_membership::get_peer_from_incoming_address(s_transport_address const* incoming_address)
{
    typedef long(__thiscall* get_peer_from_incoming_address_ptr)(c_network_session_membership* session_membership, s_transport_address const* incoming_address);
    auto get_peer_from_incoming_address_call = reinterpret_cast<get_peer_from_incoming_address_ptr>(module_base + 0x31230);
    return get_peer_from_incoming_address_call(this, incoming_address);
}

// TEST THIS
void c_network_session_membership::set_peer_connection_state(long peer_index, e_network_session_peer_state state) // inlined in ms29
{
    s_network_session_peer* session_peer = this->get_peer(peer_index);
    session_peer->connection_state = state;
    uint32_t time_elapsed = network_get_time() - session_peer->join_start_time;
    printf("MP/NET/SESSION,MEMBERSHIP: c_network_session_membership::set_peer_connection_state: [%s] peer #%d [%s] set to state %s (%d msec from start)\n",
        "00:00:00:00:00:00:00:00", // TODO - not sure how to include network_session.h to network_session_membership.h without causing errors to allow this method to run here
        peer_index,
        transport_secure_address_get_string(&session_peer->secure_address),
        network_session_peer_state_get_string(state),
        time_elapsed);
    if (state == _network_session_peer_state_established)
        this->set_join_nonce(peer_index, 0);
    this->increment_update();
}

s_network_session_peer* c_network_session_membership::get_peer(long peer_index)
{
    // TODO - assert here w/ is_peer_valid
    return &this->m_baseline.peers[peer_index];
}

const char* network_session_peer_state_get_string(e_network_session_peer_state state)
{
    return network_session_peer_states[state];
}

void c_network_session_membership::set_join_nonce(long peer_index, int64_t join_nonce)
{
    this->get_peer(peer_index)->join_nonce = join_nonce;
}

void c_network_session_membership::increment_update()
{
    this->m_baseline.update_number++;
    this->m_player_configuration_version++;
}

long c_network_session_membership::get_player_count()
{
    return this->m_baseline.player_count;
}

void c_network_session_membership::idle()
{
    void(__thiscall * idle)(c_network_session_membership* membership) = reinterpret_cast<decltype(idle)>(module_base + 0x328E0);
    idle(this);
}

bool c_network_session_membership::all_peers_established()
{
    bool(__thiscall * all_peers_established)(c_network_session_membership* membership) = reinterpret_cast<decltype(all_peers_established)>(module_base + 0x20E50);
    return all_peers_established(this);
}

long c_network_session_membership::get_observer_channel_index(long observer_channel_index)
{
    // TODO ASSERTS
    return this->m_peer_channels[observer_channel_index].channel_index;
}

long c_network_session_membership::get_host_observer_channel_index()
{
    // TODO ASSERTS
    long host_peer_index = this->host_peer_index();
    return this->get_observer_channel_index(host_peer_index);
}

long c_network_session_membership::host_peer_index()
{
    return this->m_baseline.host_peer_index;
}

long c_network_session_membership::private_slot_count()
{
    return this->m_baseline.private_slot_count;
}

long c_network_session_membership::public_slot_count()
{
    return this->m_baseline.public_slot_count;
}

bool c_network_session_membership::friends_only()
{
    return this->m_baseline.friends_only;
}

c_network_session* c_network_session_membership::get_session()
{
    return this->m_session;
}

void c_network_session_membership::set_slot_counts(long private_slot_count, long public_slot_count, bool friends_only)
{
    auto session = this->get_session();
    long managed_session_index = session->managed_session_index();
    this->m_baseline.private_slot_count = private_slot_count;
    this->m_baseline.public_slot_count = public_slot_count;
    this->m_baseline.friends_only = friends_only;
    if (session)
        managed_session_modify_slot_counts(managed_session_index, private_slot_count, public_slot_count, friends_only, this->m_baseline.peer_count);
    this->increment_update();
}

bool c_network_session_membership::has_peer_ever_been_established(long peer_index)
{
    auto peer = this->get_peer(peer_index);
    return (peer->connection_state == _network_session_peer_state_established || peer->connection_state == _network_session_peer_state_rejoining);
}

s_network_session_peer* c_network_session_membership::get_raw_peer(long peer_index)
{
    // same thing as get_peer w/o the asserts
    return &this->m_baseline.peers[peer_index];
}

e_network_session_peer_state c_network_session_membership::get_peer_connection_state(long peer_index)
{
    return this->get_peer(peer_index)->connection_state;
}

void c_network_session_membership::remove_peer(long peer_index)
{
    auto raw_peer = this->get_raw_peer(peer_index);
    auto session = this->get_session();
    // char* peer_name_ascii; // TODO
    // wchar_string_to_ascii_string(raw_peer->properties.peer_name, peer_name_ascii, 256, 0); // TODO - convert from wchar to char
    printf("MP/NET/SESSION,MEMBERSHIP: c_network_session_membership::remove_peer: [%s] removing peer #%d [%s] name [%s]\n", // this log doesn't exist in ms23
        session->get_id_string(),
        peer_index,
        transport_secure_address_get_string(&raw_peer->secure_address),
        /*peer_name_ascii*/"unknown_peer");

    void(__thiscall * remove_peer)(c_network_session_membership* membership, long peer_index) = reinterpret_cast<decltype(remove_peer)>(module_base + 0x30E50);
    return remove_peer(this, peer_index);

    /* UNFINISHED - i discovered the function still exists midway through rewriting it
    if (this->get_peer_connection_state(peer_index) >= _network_session_peer_state_connected || this->get_peer_connection_state(peer_index) == _network_session_peer_state_rejoining)
    {
        auto peer = this->get_peer(peer_index);

    }

    this->remove_peer_internal(peer_index);
    auto session_parameters = session->get_session_parameters();
    session_parameters->reset_peer_state(peer_index);
    if (session->established())
    {
        session_parameters->countdown_timer.set(0, 0, 0, 0);
    }

    // check if host peer is being removed and migrate to a new host functionality not required for HO

    this->increment_update();
    */
}

s_network_session_shared_membership* c_network_session_membership::get_current_membership()
{
    return &this->m_baseline;
}

s_network_session_shared_membership* c_network_session_membership::get_transmitted_membership(long peer_index)
{
    return &this->m_transmitted_shared_network_membership[peer_index];
}

void c_network_session_membership::set_membership_update_number(long peer_index, long update_number)
{
    // TODO - is_peer_valid assert
    this->m_transmitted_shared_network_membership[peer_index].update_number = update_number;
}