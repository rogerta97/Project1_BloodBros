#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleDebug.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "ModuleUI.h"
#include "ModuleReticle.h"
#include "ModuleFadeToBlack.h"
#include "ModulePowerUps.h"
#include "ModuleScenario.h"
#include "Scenario_Bottle.h"
#include "ModuleSceneSpace.h"
#include "ModuleTincan.h"
#include "SDL/include/SDL.h"


bool ModuleSceneSpace::Start()
{
	LOG("Loading space scene");
	
	background = App->textures->Load("sprites/background.png");

	App->player->Enable();
	App->particles->Enable();
	App->collision->Enable();
	App->enemies->Enable();
	App->debug->Enable();
	App->reticle->Enable();
	App->scenario->Enable();
	App->power_ups->Enable();
	App->UI->reset();
	App->tincan->Enable();

	App->audio->PlayMusic("Music/Main_Song.wav", 1.0f);
	

	loop_enemies();      // first loop = first wave;
	defeated_enemies = 0;
	is_backgr_destroyed = false;

	App->scenario->AddElement(DESTROYABLE_WALL, 0, 44);

	App->scenario->AddElement(DESTROYABLE_BOTTLE, 255, 383);
	App->scenario->AddElement(DESTROYABLE_BOTTLE, 290, 383);
	App->scenario->AddElement(DESTROYABLE_BOTTLE, 365, 383);
	App->scenario->AddElement(DESTROYABLE_BOTTLE, 390, 383);
	App->scenario->AddElement(DESTROYABLE_BOTTLE, 455, 383);
	App->scenario->AddElement(DESTROYABLE_BOTTLE, 480, 383);

	App->scenario->AddElement(DESTROYABLE_LIGHT, 500, 0);
	App->scenario->AddElement(DESTROYABLE_LIGHT, 300, 0);
	App->scenario->AddElement(DESTROYABLE_LIGHT, 100, 0);

	App->scenario->AddElement(DESTROYABLE_BARREL, 20, 350);
	App->scenario->AddElement(DESTROYABLE_BARREL, 85, 350);
	App->scenario->AddElement(DESTROYABLE_BARREL, 170, 350);

	App->scenario->AddElement(DESTROYABLE_BARREL, SCREEN_WIDTH - 85 - 20, 355);
	App->scenario->AddElement(DESTROYABLE_BARREL, SCREEN_WIDTH - 85 - 85, 355);
	App->scenario->AddElement(DESTROYABLE_BARREL, SCREEN_WIDTH - 85 - 170, 355);

	return true;
}

// UnLoad assets
bool ModuleSceneSpace::CleanUp()
{
	LOG("Unloading space scene");

 	App->textures->Unload(background);

	if (!(App->debug->activated_functions[NO_ENEMIES_F3]))
		App->enemies->Disable();

	if (!(App->debug->activated_functions[NO_PLAYER_F4])){
		App->player->Disable();
		App->reticle->Disable();
	}

	App->collision->Disable();
	App->particles->Disable();
	App->scenario->Disable();
	App->debug->Disable();
	App->power_ups->Disable();
	App->tincan->Disable();


	return true;
}

// Update: draw background
update_status ModuleSceneSpace::Update()
{
	if (defeated_enemies >= ENEMY_NUM_STG1 && is_backgr_destroyed){
		if (App->player->current_animation != &App->player->victory_dance){
			App->audio->PlayMusic("Music/victorydance.wav");
			App->player->current_animation->Reset();
			App->player->current_animation = &App->player->victory_dance;
			App->enemies->Disable();
			App->debug->activated_functions[NO_ENEMIES_F3] = true;
		}
		

		if (App->player->current_animation->Finished()){
			Mix_FadeOutMusic(1000);
			App->fade->FadeToBlack(this, (Module*)App->scene_score);
		}
	}  // Win condition

	current_level_time = SDL_GetTicks() - init_level_time;

	if (current_level_time > 4000 && released_enemies <= 0){
		App->enemies->AddEnemy(INDIAN_001, -20, 400);
		released_enemies++;
	}

	if (current_level_time > 6000 && released_enemies <= 1){
		App->enemies->AddEnemy(INDIAN_002, SCREEN_WIDTH + 20, 400);
		released_enemies++;
	}

	if (current_level_time > 9000 && released_enemies <= 2){
		App->enemies->AddEnemy(HORSE_001, SCREEN_WIDTH + 20, 400);
		App->enemies->AddEnemy(MOUNTED_INDIAN_001, SCREEN_WIDTH + 30, 380);
		released_enemies++;
	}

	if (current_level_time > 12000 && released_enemies <= 3){
		App->enemies->AddEnemy(BARREL_GUY, -20, 420);
		released_enemies++;
	}

	if (current_level_time > 13000 && released_enemies <= 4){
		App->enemies->AddEnemy(PIG_001, SCREEN_WIDTH + 20, 380);
		released_enemies++;
	}

	if (current_level_time > 15000 && released_enemies <= 5){
		App->enemies->AddEnemy(CART_001, SCREEN_WIDTH + 20, 330);
		released_enemies++;
	}

	if (current_level_time > 18000 && released_enemies <= 6 && is_backgr_destroyed){
		App->enemies->AddEnemy(ZEPPELIN, SCREEN_WIDTH - 95, 200);
		released_enemies++;
	}

	if (current_level_time > 21000 && released_enemies <= 7){
		if (!is_backgr_destroyed)
			App->enemies->AddEnemy(INDIAN_003, -20, 222);
		else if (is_backgr_destroyed)
			App->enemies->AddEnemy(INDIAN_003, -20, 362);

		released_enemies++;
	}

	if (current_level_time > 24000 && released_enemies <= 8){
		if (!is_backgr_destroyed)
			App->enemies->AddEnemy(INDIAN_003, -20, 222);
		else if (is_backgr_destroyed)
			App->enemies->AddEnemy(INDIAN_003, -20, 362);

		released_enemies++;
	}

	if (current_level_time > 28000)
		loop_enemies();



	App->render->Blit(background, 0, 0, NULL);
	
	return UPDATE_CONTINUE;
}

void ModuleSceneSpace::loop_enemies(){

	released_enemies = 0;

	init_level_time = SDL_GetTicks();

}

