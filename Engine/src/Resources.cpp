#include "Resources.h"
#include "Error.h"
#include "Game.h"

std::unordered_map<string, std::shared_ptr<SDL_Texture>> Resources::imageTable;
std::unordered_map<string, std::shared_ptr<Mix_Music>> Resources::musicTable;
std::unordered_map<string, std::shared_ptr<Mix_Chunk>> Resources::soundTable;
std::unordered_map<string, std::shared_ptr<TTF_Font>> Resources::fontTable;

std::shared_ptr<SDL_Texture> Resources::GetImage(string file) {
	SDL_Texture* ret;
	if(imageTable.end() == imageTable.find(file)) {
		ret=IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
		if(nullptr == ret) {
//			std::cout << WHERE <<  << file << endl;
			Error("Could not load "<<file);
		}
//		ASSERT(nullptr != ret);
		imageTable[file]= std::shared_ptr<SDL_Texture>
				(
					ret,
					[](SDL_Texture *texture)//meu primeiro uso de função labda em C++ {
						SDL_DestroyTexture(texture);
					}
				);
	}
	return imageTable[file];
}

void Resources::ClearImages(void) {
	std::unordered_map<string, std::shared_ptr<SDL_Texture>>::iterator i= imageTable.begin();
	while(i != imageTable.end()) {
		if((*i).second.unique()) {
			i= imageTable.erase(i);
		}
		else {
			i++;
		}
	}
}

std::shared_ptr<Mix_Music> Resources::GetMusic(string file) {
	Mix_Music* ret;
	if(musicTable.end() == musicTable.find(file)) {
		ret=Mix_LoadMUS(file.c_str());
		if(nullptr == ret) {
//			std::cout << WHERE <<  << file << endl;
			Error("Could not load "<<file);
		}
		musicTable[file]= std::shared_ptr<Mix_Music>
				(
					ret,
					[](Mix_Music *music)//meu segundo uso de função labda em C++ {
						Mix_FreeMusic(music);
					}
				);
	}
	return musicTable[file];
}

void Resources::ClearResources(void) {
	ClearImages();
	ClearMusic();
	ClearSound();
	ClearFonts();
}

void Resources::ClearMusic(void) {
	std::unordered_map<string, std::shared_ptr<Mix_Music>>::iterator i= musicTable.begin();
	while(i != musicTable.end()) {
		if((*i).second.unique()) {
			i= musicTable.erase(i);
		}
		else {
			i++;
		}
	}
}

std::shared_ptr<Mix_Chunk> Resources::GetSound(string file) {
	Mix_Chunk* ret;
	if(soundTable.end() == soundTable.find(file)) {
		ret= Mix_LoadWAV(file.c_str());
		if(nullptr == ret) {
//			std::cout << WHERE <<  << file << endl;
			Error("Could not load "<<file);
		}
//		ASSERT(nullptr != ret);
		soundTable[file]= std::shared_ptr<Mix_Chunk>
				(
					ret,
					[](Mix_Chunk *chunck)//meu terceiro uso de função labda em C++ {
						Mix_FreeChunk(chunck);
					}
				);
	}
	return soundTable[file];
}

std::shared_ptr<TTF_Font> Resources::GetFont(string file, int fontSize) {
	TTF_Font* ret;
	if(fontTable.end() == fontTable.find(file+std::to_string(fontSize))) {
		ret= TTF_OpenFont (file.c_str(), fontSize);
		if(nullptr == ret) {
//			std::cout << WHERE <<  << file << endl;
			Error("Could not load "<<file);
		}
		fontTable[file+std::to_string(fontSize)]= std::shared_ptr<TTF_Font>
				(
					ret,
					[](TTF_Font *font)//meu quarto uso de função labda em C++ {
						TTF_CloseFont (font);
					}
				);
	}
	return fontTable[file+std::to_string(fontSize)];
}

void Resources::ClearSound(void) {
	std::unordered_map<string, std::shared_ptr<Mix_Chunk>>::iterator i= soundTable.begin();
	while(i != soundTable.end()) {
		if((*i).second.unique()) {
			i= soundTable.erase(i);
		}
		else {
			i++;
		}
	}
}

void Resources::ClearFonts(void) {
	std::unordered_map<string, std::shared_ptr<TTF_Font>>::iterator i= fontTable.begin();
	while(i != fontTable.end()) {
		if((*i).second.unique()) {
			i= fontTable.erase(i);
		}
		else {
			i++;
		}
	}
}


