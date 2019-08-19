#include <ape/input/context.h>

namespace ape {
    namespace input {
        Context::Context(int priority, const std::string& path) : Persistent(path), priority(priority) {

        }

        void Context::addCallback(InputEventInfo info, const std::string& name, std::function<bool(InputEventInfo)> callback) {
            keymaps[info] = name;
            callbacks[name] = callback;            
        }

        void Context::addCallback(const std::string& name, std::function<bool(InputEventInfo)> callback) {
            callbacks[name] = callback;            
        }

        bool Context::compare(Context& c1, Context& c2) {
            return c1.priority < c2.priority;
        }

        void Context::setActive(bool setting) {
            active = setting;
        }

        bool Context::getActive() {
            return active;
        }

        bool Context::consume(InputEventInfo info) {
            if (!active || keymaps.find(info) == keymaps.end()) {
                return true;
            }

            return callbacks[keymaps[info]](info);
        }

        void Context::toJson() {
            this->jsonObj.clear();
            for (const auto& pair : keymaps) {
                std::string inputType;
                std::string eventType;
                if (pair.first.inputType == InputType::ACTION) {
                    inputType = "actions";
                    if (pair.first.eventType == EventType::KEY_DOWN) {
                        eventType == "keydown";
                    } else if (pair.first.eventType == EventType::KEY_UP) {
                        eventType == "keyup";
                    } else if (pair.first.eventType == EventType::MOUSE_DOWN) {
                        eventType == "mousedown";
                    } else if (pair.first.eventType == EventType::MOUSE_UP) {
                        eventType == "mouseup";
                    } else {
                        std::cout << "Context error: Action event not supported.\n";
                    }
                } else if (pair.first.inputType == InputType::STATE) {
                    inputType = "states";
                    std::string eventType;
                    if (pair.first.eventType == EventType::KEY_DOWN) {
                        eventType == "keydown";
                    } else if (pair.first.eventType == EventType::KEY_UP) {
                        eventType == "keyup";
                    } else if (pair.first.eventType == EventType::MOUSE_DOWN) {
                        eventType == "mousedown";
                    } else if (pair.first.eventType == EventType::MOUSE_UP) {
                        eventType == "mouseup";
                    } else {
                        std::cout << "Context error: Action event not supported.\n";
                    }
                } else if (pair.first.inputType == InputType::RANGE) {
                    inputType = "ranges";
                    /* TODO: Ranges */
                    std::cout << "Context error: range inputs not supported yet.\n";
                }

                jsonObj[inputType][eventType][std::to_string(pair.first.info.raw)] = pair.second;
            }
        }

        /* TODO: Input validity checks & parsing errors */
        void Context::fromJson() {
            keymaps.clear();
            /* TODO: Clean this up, reduce repetition */
            for (const auto& pair : jsonObj.items()) {
                InputEventInfo info;
                bool error = false;
                if (pair.key() == "actions") {
                    info.inputType = InputType::ACTION;
                    for (const auto& actionPair : jsonObj[pair.key()].items()) {
                        if (actionPair.key() == "keydown") {
                            info.eventType = EventType::KEY_DOWN;
                            for (const auto& values : jsonObj[pair.key()][actionPair.key()].items()) {
                                info.info.keyCode = static_cast<KeyCode>(std::stoi(values.key()));
                                keymaps[info] = values.value();
                            }
                        } else if (actionPair.key() == "keyup") {
                            info.eventType = EventType::KEY_UP;
                            for (const auto& values : jsonObj[pair.key()][actionPair.key()].items()) {
                                info.info.keyCode = static_cast<KeyCode>(std::stoi(values.key()));
                                keymaps[info] = values.value();
                            }
                        } else if (actionPair.key() == "mousedown") {
                            info.eventType = EventType::MOUSE_DOWN;
                            for (const auto& values : jsonObj[pair.key()][actionPair.key()].items()) {
                                info.info.mouseButton = static_cast<MouseButton>(std::stoi(values.key()));
                                keymaps[info] = values.value();
                            }
                        } else if (actionPair.key() == "mouseup") {
                            info.eventType = EventType::MOUSE_UP;
                            for (const auto& values : jsonObj[pair.key()][actionPair.key()].items()) {
                                info.info.mouseButton = static_cast<MouseButton>(std::stoi(values.key()));
                                keymaps[info] = values.value();
                            }
                        } else {
                            std::cout << "Context load error: Action event " << actionPair.key() << " not supported.\n";
                            error = true;
                        }
                    }
                } else if (pair.key() == "states") {
                    info.inputType = InputType::STATE;
                    for (const auto& statePair : jsonObj[pair.key()].items()) {
                        if (statePair.key() == "keypressed") {
                            info.eventType = EventType::KEY_PRESS;
                            for (const auto& values : jsonObj[pair.key()][statePair.key()].items()) {
                                info.info.keyCode = static_cast<KeyCode>(std::stoi(values.key()));
                                keymaps[info] = values.value();
                            }
                        } else if (statePair.key() == "mousedown") {
                            info.eventType = EventType::MOUSE_DOWN;
                            for (const auto& values : jsonObj[pair.key()][statePair.key()].items()) {
                                info.info.mouseButton = static_cast<MouseButton>(std::stoi(values.key()));
                                keymaps[info] = values.value();
                            }
                        } else if (statePair.key() == "mouseup") {
                            info.eventType = EventType::MOUSE_UP;
                            for (const auto& values : jsonObj[pair.key()][statePair.key()].items()) {
                                info.info.mouseButton = static_cast<MouseButton>(std::stoi(values.key()));
                                keymaps[info] = values.value();
                            }
                        } else {
                            std::cout << "Context load error: State event " << statePair.key() << " not supported.\n";
                            error = true;
                        }
                    }
                } else if (pair.key() == "ranges") {
                    info.inputType = InputType::RANGE;
                    for (const auto& rangePair : jsonObj[pair.key()].items()) {
                        std::cout << "Context load error: Ranges not supported yet.\n";
                    }
                } else {
                    std::cout << "Context load error: Input type " << pair.key() << " not supported.\n";
                    error = true;
                }
            }
        }

        std::priority_queue<Context, std::vector<Context>, std::function<bool(Context&, Context&)>> globalContextChain(Context::compare);
    }
}