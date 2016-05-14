#include "Application.h"
#include "Enemy_indian_002.h"
#include "Path.h"
#include "ModuleCollision.h"
#include "ModuleSceneSpace.h"
#include "p2Point.h"
#include "ModuleParticles.h"

Enemy_Indian_002::Enemy_Indian_002(int x, int y) : Enemy(x, y)
{
	walking_left.PushBack({ 762, 49, 96, 114 });
	walking_left.PushBack({ 868, 49, 78, 115 });
	walking_left.PushBack({ 959, 48, 52, 116 });
	walking_left.PushBack({ 1021, 49, 97, 112 });
	walking_left.PushBack({ 1136, 46, 80, 116 });
	walking_left.PushBack({ 1240, 47, 55, 116 });
	walking_left.speed = 0.1f;

	walking_right.PushBack({ 27, 46, 80, 116 });
	walking_right.PushBack({ 94, 49, 97, 112 });
	walking_right.PushBack({ 187, 48, 52, 116 });
	walking_right.PushBack({ 294, 49, 78, 115 });
	walking_right.PushBack({ 358, 49, 96, 114 });
	walking_right.PushBack({ 446, 47, 55, 116 });
	walking_right.speed = 0.1f;

	shooting.PushBack({ 554, 50, 100, 113 });
	shooting.PushBack({ 666, 19, 82, 145 });
	shooting.PushBack({ 554, 50, 100, 113 });
	shooting.speed = 0.05f;
	shooting.loop = false;



	collider = App->collision->AddCollider({ position.x, position.y - 116, 55, 116 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	orig_pos.x = x;
	orig_pos.y = y;


	Indian_002_path.PushBack({ -2, 0 }, 100, &walking_right);
	Indian_002_path.PushBack({ 0, 0 }, 100, &shooting);
	Indian_002_path.PushBack({ 2, 0 }, 500, &walking_left);

}

void Enemy_Indian_002::Update()
{

	if (animation != &dying)
		position = orig_pos + Indian_002_path.GetCurrentSpeed(&animation);


	if (last_anim != animation){

		if (animation == &walking_left || animation == &walking_right)
			state = EN_ST_WALKING;
		else if (animation == &dying)
			state = EN_ST_DYING;
		else{
			state = EN_ST_SHOOTING;
			App->particles->AddParticle(App->particles->enemy_shot, position.x + 25, position.y - 120, COLLIDER_ENEMY_SHOT, 400);
		}

		last_anim = animation;

	}
}

