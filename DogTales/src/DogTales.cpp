#include <src/DogTales.hpp>

void DogTales::on_key(bave::KeyInput const& key_input) {
	if (key_input.key == bave::Key::eEscape && key_input.action == bave::Action::eRelease) { get_app().shutdown(); }
}

void DogTales::render() const {
	if (auto shader = get_app().load_shader("shaders/default.vert", "shaders/default.frag")) {
		m_shape.draw(*shader);
	}
}
