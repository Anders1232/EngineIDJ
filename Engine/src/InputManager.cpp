#include "InputManager.h"
#include "string.h"
#include "Error.h"
//#include "Camera.h"

InputManager::InputManager():quitRequested(false), updateCounter(0), mouseX(0), mouseY(0), mouseScroolUpdate(0)
{

	memset(mouseState, 0, 6*sizeof(bool));
	memset(mouseUpdate, 0, 6*sizeof(int));

}
InputManager::~InputManager()
{
}
InputManager& InputManager::GetInstance(void)
{
	static InputManager inputManager;
	return inputManager;
}

void InputManager::Update(){

	SDL_Event event;

    updateCounter ++;
    quitRequested = false;

    // Obtenha as coordenadas do mouse
    SDL_GetMouseState(&mouseX, &mouseY);

    // SDL_PollEvent retorna 1 se encontrar eventos, zero caso contrário
    while (SDL_PollEvent(&event)){

        // Se o evento for quit, setar a flag para terminação

        if(event.type == SDL_QUIT){

            quitRequested = true;

        }
        // Se o evento for clique...
        else if(event.type == SDL_MOUSEBUTTONDOWN){

        	 mouseState[event.button.button] = true;
        	 mouseUpdate[event.button.button] = updateCounter;
            
        }
        else if(event.type == SDL_MOUSEBUTTONUP ) {
            
            mouseState[event.button.button] = false;

        }
        else if(SDL_MOUSEWHEEL == event.type){

			mouseScroolState= Vec2(event.wheel.x, event.wheel.y);
			mouseScroolUpdate= updateCounter;

		}
        else if(event.type == SDL_KEYDOWN){

        	if(!event.key.repeat){

				keyState[event.key.keysym.sym] = true;
	        	keyUpdate[event.key.keysym.sym] = updateCounter;
	        }

        }
        else if(event.type == SDL_KEYUP){

        	keyState[event.key.keysym.sym] = false;

        }
        else if(event.type == SDL_CONTROLLERDEVICEADDED){

        	if( SDL_IsGameController(event.cdevice.which)){
    			//Adiciona o controle
        		SDL_GameController *pad = SDL_GameControllerOpen(event.cdevice.which);
        		//Caso exista um pad o mapeia para o controle
        		if(pad){

            		SDL_Joystick *joy = SDL_GameControllerGetJoystick(pad);
            		int instanceID = SDL_JoystickInstanceID(joy);

            		padToController[event.cdevice.which] = pad;
            
        		}
    		}
         
        }
		else if(event.type == SDL_CONTROLLERDEVICEREMOVED){
           
            try{

            	SDL_GameController *pad = padToController.at(event.cdevice.which);
            	SDL_GameControllerClose(pad);

            }
            catch(const std::out_of_range& oor){

            	Error("Tentou retirar controle que não existe?!?");

            }
        
        }
		else if(event.type == SDL_CONTROLLERBUTTONDOWN){

			controllerState[event.cbutton.button] = true;
	        controllerUpdate[event.cbutton.button] = updateCounter;

		}

        else if(event.type == SDL_CONTROLLERBUTTONUP){

            controllerState[event.cbutton.button] = false;

        }

        else if(event.type == SDL_CONTROLLERAXISMOTION){
            
            if(event.caxis.axis == SDL_CONTROLLER_AXIS_TRIGGERLEFT){

                controllerState[SDL_CONTROLLER_AXIS_TRIGGERLEFT] = true;
                controllerUpdate[SDL_CONTROLLER_AXIS_TRIGGERLEFT] = updateCounter;

            }
            else if(event.caxis.axis == SDL_CONTROLLER_AXIS_TRIGGERRIGHT){

                controllerState[SDL_CONTROLLER_AXIS_TRIGGERRIGHT] = true;
                controllerUpdate[SDL_CONTROLLER_AXIS_TRIGGERRIGHT] = updateCounter;

            }
            else if(event.caxis.axis != SDL_CONTROLLER_AXIS_INVALID){

                SDL_GameController *pad = padToController.at(event.cdevice.which);

                int16_t StickX = SDL_GameControllerGetAxis(pad,SDL_CONTROLLER_AXIS_LEFTX);
            	int16_t StickY = SDL_GameControllerGetAxis(pad, SDL_CONTROLLER_AXIS_LEFTY);

                controllerStickState = Vec2((float)StickX,(float)StickY);
    			controllerStickUpdate = updateCounter;

            }
        
        }

    }
}

bool InputManager::KeyPress(int key) const{

  try{return(keyUpdate.at(key) == updateCounter);}
  catch (const std::out_of_range& oor){return false;}

}

bool InputManager::KeyRelease(int key) const{

	try{return(keyUpdate.at(key) != updateCounter);}
  	catch (const std::out_of_range& oor){return false;}

}

bool InputManager::IsKeyDown(int key) const{

	try{return(keyState.at(key) == true);}
  	catch (const std::out_of_range& oor){return false;}

}

bool InputManager::MousePress(int button) const{

	return(mouseUpdate[button] == updateCounter);

}

bool InputManager::MouseRelease(int button) const{

	return(mouseUpdate[button] != updateCounter);

}
bool InputManager::IsMouseDown(int button) const{

	return(mouseState[button] == true);

}

int InputManager::GetMouseX() const{

	return(mouseX);

}
int InputManager::GetMouseY() const{

	return(mouseY);

}
bool InputManager::QuitRequested() const{

	return(quitRequested);

}

Vec2 InputManager::GetMousePos() const{

	return Vec2(mouseX, mouseY);

}

Vec2 InputManager::MouseScroll(void) const{

	return mouseScroolState;

}

bool InputManager::IsMouseScrolling(void) const{

	return (mouseScroolUpdate == updateCounter);

}


