#include <src/player.hpp>

Player::Player(glm::vec2 const world_space) : m_world_space(world_space), m_vel(0.0f, 0.0f) {
	m_sprite.set_size(size_v);
}

void Player::tick(bave::Seconds const dt) {
	// Update the player's position based on velocity.
	m_sprite.transform.position += m_vel * dt.count();

	handle_wall_collision();
}

void Player::draw(bave::Shader& shader) const { m_sprite.draw(shader); }

void Player::update_movement(float dx, float dy) {
	// Modify the player's movement based on the specified direction.
	// Adjust this function based on your game logic.
	m_vel.x = dx * speed_v.x;
	m_vel.y = dy * speed_v.y;
}

void Player::handle_input(bave::KeyInput const& key_input) {
	// Update the velocity based on WASD input
	if (key_input.key == bave::Key::eW) {
		update_movement(0, 1);
	} else if (key_input.key == bave::Key::eA) {
		update_movement(-1, 0);
	} else if (key_input.key == bave::Key::eS) {
		update_movement(0, -1);
	} else if (key_input.key == bave::Key::eD) {
		update_movement(1, 0);
	}
}

void Player::handle_wall_collision() {
	auto& position = m_sprite.transform.position;
	// bounce_rect represents the play area for the sprite, ie the limits for its centre.
	// the size is simply the total space minus the sprite size, centered at the origin.
	// the second argument (glm::vec2{0.0f}) is the default value and can be omitted here.
	auto const bounce_rect = bave::Rect<>::from_size(m_world_space - m_sprite.get_size(), glm::vec2{0.0f});

	// if the sprite's position exceeds the play area, the corresponding velocity component needs to flip.
	if (position.x < bounce_rect.top_left().x || position.x > bounce_rect.bottom_right().x) { m_vel.x *= -1.0f; }
	if (position.y > bounce_rect.top_left().y || position.y < bounce_rect.bottom_right().y) { m_vel.y *= -1.0f; }

	// clamp the position to the play area.
	// bottom_left() gives us the minimum x and y whereas top_right() gives us the maximum.
	position = glm::clamp(position, bounce_rect.bottom_left(), bounce_rect.top_right());
}
