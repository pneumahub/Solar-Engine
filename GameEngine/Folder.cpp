
#include "Folder.hpp"
#include <iostream>
namespace Solar {
	//Inherited from Instance
	extern struct Enums Enum;
	void Folder::AddChild(Instance* child)
	{
		this->children.emplace(this->children.size() + 1, child);
		child->Parent = this;
	}
	void Folder::Tick(float dt){
		if (this->Parent == nil)
		{
			return;
		}
		if (this->Enabled) {
			if (this->_body.getSize() != this->Parent->_body.getSize() || this->_body.getPosition() != this->Parent->_body.getPosition())
			{
				this->_body.setPosition(this->Parent->_body.getPosition());
				this->_body.setSize(this->Parent->_body.getSize());
			}
			for (auto& x : this->children) {
				x.second->Tick(dt);
			}
		}
	}
	void Folder::Render(float dt) {
		if (this->Enabled) {
			for (auto& x : this->children) {
				x.second->Render(dt);
			}
		}
	}

	void Folder::HandleEvents()
	{
		//Events


		for (auto& x : this->children) {
			x.second->HandleEvents();
		}
	}

	void Folder::HookEvent(std::string Event, std::function<void(Instance * frame)> function)
	{
		EventStruct fun;
		fun.StoredFunction = function;
		fun.EventName = Event;
		this->EventQueue.emplace(this->EventQueue.size() + 1, fun);
	}
	void Folder::FireEvent(std::string Event)
	{
		for (auto& x : this->EventQueue)
			if (x.second.EventName == Event)
				x.second.StoredFunction(this);
	}
}