#include "Main.h"

#include "Script.h"

#include "Time.h"
#include "Color.h"
#include "Easing.h"
#include "Bullet.h"
#include "Laser.h"
#include "Player.h"

Vec2D BossPos = Vec2D(CENTER_X, 250);
Color bgGamingColor(0, 0, 0);
Color gamingColor(0, 0, 0);
double RandTMP = 0;

void
Function() {
	gamingColor = GetColorHSV((frame) % 360, 1, 1);
	if (frame < Beat2Frame(240, 4, 1)) {
		BossPos = Vec2D(CENTER_X + sin(Rad(frame) * 5) * 150, 250 + sin(Rad(frame) * 3) * 50);
		DrawBox(0, 0, 1920, 1080, GetColor(Easing(EASEINQUAD, frame / 60.0f, 0, 255), Easing(EASEINQUAD, frame / 60.0f, 0, 255), Easing(EASEINQUAD, frame / 60.0f, 0, 255)), 1);
		DrawRotaGraph(BossPos.x, BossPos.y, 1.0f, 0.0f, imgRes.EnemyGH[0], 1);
	}
	if (frame == 60) {
		PlaySoundFile("./res/snd/bgm/Not The Ended.wav", DX_PLAYTYPE_BACK);
	}
	if (frame > Beat2Frame(240, 4, 1)) {
		for (int i = 0; i < 8000; i++) {
			bgGamingColor = GetColorHSV((frame + i) % 360, 1, 1);
			for (int j = 0; j < 6; j++) {
				DrawLine(
					CENTER_X + sin(ICHIDO * ((frame + i / 8.0f) / 1) + TAU / 6 * j) * (i % 1000),
					CENTER_Y + cos(ICHIDO * ((frame + i / 8.0f) / 1) + TAU / 6 * j) * (i % 1000),
					CENTER_X + sin(ICHIDO * ((frame + i / 8.0f) / 1) + TAU / 6 * (j + 2.0f)) * (i % 1000),
					CENTER_Y + cos(ICHIDO * ((frame + i / 8.0f) / 1) + TAU / 6 * (j + 2.0f)) * (i % 1000),
					GetColor(bgGamingColor.r, bgGamingColor.g, bgGamingColor.b)
				);
			}
		}
	}
	if (frame > Beat2Frame(240, 4, 1) && frame < Beat2Frame(240, 4, 5)) {
		SmartSetDrawBlendMode(BLEND_ADD, 255);
		DrawBox(0, 0, 1920, 1080, GetColor(Easing(EASEINQUAD, frame / 240.0f - 0.25f, 255, 0), Easing(EASEINQUAD, frame / 240.0f - 0.25f, 255, 0), Easing(EASEINQUAD, frame / 240.0f - 0.25f, 255, 0)), 1);
		SmartSetDrawBlendMode(BLEND_NOBLEND, 255);
	}
	if (frame > Beat2Frame(240, 4, 1) && frame < Beat2Frame(240, 4, 17)) {
		BossPos = Vec2D(CENTER_X + sin(Rad(frame) * 5) * 150, 250 + sin(Rad(frame) * 3) * 50);
		DrawRotaGraph(BossPos.x, BossPos.y, 1.0f, 0.0f, imgRes.EnemyGH[0], 1);
		RandTMP = std::fmod(rng() / 100.0f, 360);
		if (frame % 15 == 0) {
			CreateBulletGroup(BossPos, gamingColor, B_MIDIAM, BLEND_NOBLEND, 255, 1, 16, 16, 0, 0, 1.0f, 1.0f, 0, 0, 16, TAU, 0, RandTMP, RandTMP, 0, 0, 10, 10, 0, 0);
		}
		if (frame % Beat2Frame(960, 4, 0.25f) == 0) {
			if (frame > 285 && frame < 300) {
				CreateBulletGroup(BossPos, gamingColor, B_MIDIAM, BLEND_NOBLEND, 255, 1, 16, 16, 0, 0, 1.0f, 1.0f, 0, 0, 24, TAU, 1, TAU / 48, TAU / 48, 0, 0, 20, 20, 0, 0);
			}
			if (frame > 765 && frame < 780) {
				CreateBulletGroup(BossPos, gamingColor, B_MIDIAM, BLEND_NOBLEND, 255, 1, 16, 16, 0, 0, 1.0f, 1.0f, 0, 0, 24, TAU, 1, TAU / 48, TAU / 48, 0, 0, 20, 20, 0, 0);
			}
		}
	}
	if (frame > Beat2Frame(240, 4, 17) && frame < Beat2Frame(240, 4, 48.75)) {
		BossPos = Vec2D(CENTER_X + sin(Rad(frame * 2)) * 50, CENTER_Y + sin(Rad(frame * 1.5) * 1.3) * 50);
		DrawRotaGraph(BossPos.x, BossPos.y, 1.0f, 0.0f, imgRes.EnemyGH[0], 1);
		CreateBulletGroup(BossPos, GetColorHSV(std::fmod(frame, 360), 1, 1), B_LIGHT, BLEND_ADD, 255, 1, 10.0f, 10.0f, EASEINQUAD, 120, 2.0f, 2.0f, EASEINQUAD, 120, 4, TAU, 0, Rad(frame + sin(Rad(frame * 2 + sin(Rad(frame * 2)) * 20)) * 20), Rad(frame + 80 + sin(Rad(frame * 1.25)) * 20), EASEOUTQUAD, 240, -10.0f + sin(Rad(frame * 1.25)) * 2, 10.0f + sin(Rad(frame * 1.5)) * 1.5, EASEINQUAD, 120);
		if (frame % 15 == 0) {
			CreateBulletGroup(BossPos, gamingColor, B_MIDIAM, BLEND_NOBLEND, 255, 1, 16, 16, 0, 0, 1.0f, 1.0f, 0, 0, 4, TAU, 1, 0, 0, 0, 0, 0.5, 20, EASEINCUBIC, 30);
		}
	}
	if (frame == Beat2Frame(240, 4, 49)) {
		for (int i = 0; i < Bullets.size(); i++) {
			Bullets[i].alive = 0;
		}
	}
	if (frame > Beat2Frame(240, 4, 49) && frame < Beat2Frame(240, 4, 75)) {
		DrawBox(0, 0, 1920, 1080, GetColor(C_WHITE), 1);
	}
	if (frame > Beat2Frame(240, 4, 49) && frame < Beat2Frame(240, 4, 50)) {
		BossPos = Vec2D(CENTER_X, 250);
		DrawRotaGraph(BossPos.x, BossPos.y, 1.0f, 0.0f, imgRes.EnemyGH[0], 1);
		CreateBulletGroup(BossPos, Color(C_BLACK), B_MIDIAM, BLEND_NOBLEND, 255, 0, 16, 16, 0, 0, 1.0f, 1.0f, 0, 0, 128, TAU, 1, TAU / 128, TAU / 128, 0, 0, 25, 25, 0, 0);
	}
	if (frame > Beat2Frame(240, 4, 50) && frame < Beat2Frame(240, 4, 53.5)) {
		DrawRotaGraph(BossPos.x, BossPos.y, 1.0f, 0.0f, imgRes.EnemyGH[0], 1);
		if (frame % 15 == 0) {
			RandTMP = std::fmod(rng() / 100.0f, 360);
			CreateBulletGroup(BossPos, Color(C_BLACK), B_NORMAL, BLEND_NOBLEND, 255, 1, 4, 4, 0, 0, 1.0f, 1.0f, 0, 0, 64, TAU, 0, RandTMP, RandTMP, 0, 0, 25, 3, EASEINCUBIC, 30);
		}
	}
	if (frame > Beat2Frame(240, 4, 53.5) && frame < Beat2Frame(240, 4, 54)) {
		CreateBulletGroup(BossPos, Color(C_BLACK), B_MIDIAM, BLEND_NOBLEND, 255, 0, 16, 16, 0, 0, 1.0f, 1.0f, 0, 0, 128, TAU, 1, TAU / 128, TAU / 128, 0, 0, 25, 25, 0, 0);
	}
	if (frame > Beat2Frame(240, 4, 54) && frame < Beat2Frame(240, 4, 57)) {
		DrawRotaGraph(BossPos.x, BossPos.y, 1.0f, 0.0f, imgRes.EnemyGH[0], 1);
		if (frame % 15 == 0) {
			RandTMP = std::fmod(rng() / 100.0f, 360);
			CreateBulletGroup(BossPos, Color(C_BLACK), B_MIDIAM, BLEND_NOBLEND, 255, 1, 8, 16, 16, 0, 1.0f, 1.0f, 0, 0, 48, TAU, 0, RandTMP, RandTMP, 0, 0, 25, 3, EASEINCUBIC, 30);
		}
	}
	if (frame > Beat2Frame(240, 4, 57) && frame < Beat2Frame(240, 4, 58)) {
		CreateBulletGroup(BossPos, Color(C_BLACK), B_MIDIAM, BLEND_NOBLEND, 255, 0, 16, 16, 0, 0, 1.0f, 1.0f, 0, 0, 128, TAU, 1, TAU / 128, TAU / 128, 0, 0, 25, 25, 0, 0);
	}
	if (frame > Beat2Frame(240, 4, 58) && frame < Beat2Frame(240, 4, 62)) {
		if (frame % 2 == 0) {
			CreateBulletGroup(BossPos, Color(C_BLACK), B_MIDIAM, BLEND_NOBLEND, 255, 0, 16, 16, 0, 0, 1.0f, 1.0f, 0, 0, 128, Easing(LINEAR, (double)(frame - Beat2Frame(240, 4, 58)) / (double)Beat2Frame(240, 4, 4), 0, Rad(359)), 0, Rad(90), Rad(90), LINEAR, 15, 20, 30, EASEINCUBIC, 30);
		}
		screenRotateZ = Easing(LINEAR, (double)(frame - Beat2Frame(240, 4, 58)) / (double)Beat2Frame(240, 4, 4), 0, TAU);
	}
	if (frame == Beat2Frame(240, 4, 62)) {
		screenRotateZ = 0;
		CreateBulletGroup(BossPos, Color(C_BLACK), B_BIG, BLEND_ADD, 255, 0, 64, 64, 0, 0, 1.0f, 1.0f, 0, 0, 16, TAU, 2, 0, 0, 0, 0, 20, 30, EASEINCUBIC, 30);
	}
	if (frame == Beat2Frame(240, 4, 62.25)) {
		RandTMP = std::fmod(rng() / 100.0f, 360);
		CreateBulletGroup(BossPos, Color(C_BLACK), B_NORMAL, BLEND_NOBLEND, 255, 1, 4, 4, 0, 0, 1.0f, 1.0f, 0, 0, 32, TAU, 0, RandTMP, RandTMP, 0, 0, 20, 30, EASEINCUBIC, 30);
	}
	if (frame == Beat2Frame(240, 4, 62.375)) {
		RandTMP = std::fmod(rng() / 100.0f, 360);
		CreateBulletGroup(BossPos, Color(C_BLACK), B_NORMAL, BLEND_NOBLEND, 255, 1, 4, 4, 0, 0, 1.0f, 1.0f, 0, 0, 32, TAU, 0, RandTMP, RandTMP, 0, 0, 20, 30, EASEINCUBIC, 30);
	}
	if (frame == Beat2Frame(240, 4, 62.5)) {
		CreateBulletGroup(BossPos, Color(C_BLACK), B_BIG, BLEND_ADD, 255, 1, 64, 64, 0, 0, 1.0f, 1.0f, 0, 0, 16, TAU, 2, 0, 0, 0, 0, 20, 30, EASEINCUBIC, 30);
	}
	if (frame > Beat2Frame(240, 4, 62.75) && frame < Beat2Frame(240, 4, 63)) {
		CreateBulletGroup(BossPos, Color(C_BLACK), B_MIDIAM, BLEND_NOBLEND, 255, 0, 16, 16, 0, 0, 1.0f, 1.0f, 0, 0, 128, TAU, 1, TAU / 128, TAU / 128, 0, 0, 25, 25, 0, 0);
	}
	if (frame == Beat2Frame(240, 4, 63)) {
		CreateBulletGroup(BossPos, Color(C_BLACK), B_BIG, BLEND_ADD, 255, 0, 64, 64, 0, 0, 1.0f, 1.0f, 0, 0, 16, TAU, 2, 0, 0, 0, 0, 20, 30, EASEINCUBIC, 30);
	}
	if (frame > Beat2Frame(240, 4, 63.25) && frame < Beat2Frame(240, 4, 63.5)) {
		CreateBulletGroup(BossPos, Color(C_BLACK), B_MIDIAM, BLEND_NOBLEND, 255, 0, 16, 16, 0, 0, 1.0f, 1.0f, 0, 0, 128, TAU, 1, TAU / 128, TAU / 128, 0, 0, 25, 25, 0, 0);
	}
	if (frame == Beat2Frame(240, 4, 63.5)) {
		CreateBulletGroup(BossPos, Color(C_BLACK), B_BIG, BLEND_ADD, 255, 0, 64, 64, 0, 0, 1.0f, 1.0f, 0, 0, 16, TAU, 2, 0, 0, 0, 0, 20, 30, EASEINCUBIC, 30);
	}
	if (frame > Beat2Frame(240, 4, 63.75) && frame < Beat2Frame(240, 4, 64)) {
		CreateBulletGroup(BossPos, Color(C_BLACK), B_MIDIAM, BLEND_NOBLEND, 255, 0, 16, 16, 0, 0, 1.0f, 1.0f, 0, 0, 128, TAU, 1, TAU / 128, TAU / 128, 0, 0, 25, 25, 0, 0);
	}
	if (frame == Beat2Frame(240, 4, 67)) {
		CreateSimpleBulletGroup(BossPos, Color(C_BLACK), B_NORMAL, BLEND_NOBLEND, 255, 4, 1.0f, 64, TAU, 1, 0, 20);
	}
	if (frame == Beat2Frame(240, 4, 67.25)) {
		CreateSimpleBulletGroup(BossPos, Color(C_BLACK), B_NORMAL, BLEND_NOBLEND, 255, 4, 1.0f, 64, TAU, 1, 0, 20);
	}
	if (frame == Beat2Frame(240, 4, 67.5)) {
		CreateSimpleBulletGroup(BossPos, Color(C_BLACK), B_NORMAL, BLEND_NOBLEND, 255, 4, 1.0f, 64, TAU, 1, 0, 20);
	}
	if (frame == Beat2Frame(240, 4, 67.625)) {
		CreateSimpleBulletGroup(BossPos, Color(C_BLACK), B_NORMAL, BLEND_NOBLEND, 255, 4, 1.0f, 64, TAU, 1, 0, 20);
	}
	if (frame == Beat2Frame(240, 4, 67.75)) {
		CreateSimpleBulletGroup(BossPos, Color(C_BLACK), B_NORMAL, BLEND_NOBLEND, 255, 4, 1.0f, 64, TAU, 1, 0, 20);
	}
	if (frame == Beat2Frame(240, 4, 67.875)) {
		CreateSimpleBulletGroup(BossPos, Color(C_BLACK), B_NORMAL, BLEND_NOBLEND, 255, 4, 1.0f, 64, TAU, 1, 0, 20);
	}
	if (frame > Beat2Frame(240, 4, 69) && frame < Beat2Frame(240, 4, 71)) {
		CreateBullet(Vec2D(BossPos.x + sin(Rad(frame) * 12) * 150, BossPos.y + sin(Rad(frame) * 8) * 150), Color(C_RED), B_NORMAL, BLEND_NOBLEND, 255, 1, 4, 4, 0, 0, 1.0f, 1.0f, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0);
		CreateBullet(Vec2D(BossPos.x + sin(Rad(frame) * 8) * 150, BossPos.y + sin(Rad(frame) * 12) * 150), Color(C_BLUE), B_NORMAL, BLEND_NOBLEND, 255, 1, 4, 4, 0, 0, 1.0f, 1.0f, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0);
		CreateBullet(Vec2D(BossPos.x + sin(Rad(frame) * 16) * 150 - sin(Rad(frame) * 4) * 150, BossPos.y + cos(Rad(frame) * -16) * 150 - cos(Rad(frame) * 4) * -150), Color(C_GREEN), B_NORMAL, BLEND_NOBLEND, 255, 1, 4, 4, 0, 0, 1.0f, 1.0f, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0);
	}
	if (frame == Beat2Frame(240, 4, 71)) {
		for (int i = 0; i < Bullets.size(); i++) {
			Bullets[i].startSpeed = 20;
			Bullets[i].endSpeed = 20;
			Bullets[i].speed = 20;
		}
	}
	if (frame > Beat2Frame(240, 4, 71) && frame < Beat2Frame(240, 4, 77)) {
		screenRotateZ = Easing(LINEAR, (double)(frame - Beat2Frame(240, 4, 71)) / (double)Beat2Frame(240, 4, 6), 0, TAU * 12);
	}
	if (frame == Beat2Frame(240, 4, 77)) {
		screenRotateZ = 0;
	}
	if (frame > Beat2Frame(240, 4, 77) && frame < Beat2Frame(240, 4, 93)) {
		BossPos = Vec2D(CENTER_X + sin(Rad(frame * 2)) * 50, CENTER_Y + sin(Rad(frame * 1.5) * 1.3) * 50);
		DrawRotaGraph(BossPos.x, BossPos.y, 1.0f, 0.0f, imgRes.EnemyGH[0], 1);
		CreateBulletGroup(BossPos, GetColorHSV(std::fmod(frame, 360), 1, 1), B_UNKO, BLEND_ADD, 255, 1, 24.0f, 24.0f, EASEINQUAD, 120, 1.5f, 1.5f, EASEINQUAD, 120, 4, TAU, 0, Rad(frame + sin(Rad(frame * 2 + sin(Rad(frame * 2)) * 20)) * 20), Rad(frame + 80 + sin(Rad(frame * 1.25)) * 20), EASEOUTQUAD, 240, -10.0f + sin(Rad(frame * 1.25)) * 2, 10.0f + sin(Rad(frame * 1.5)) * 1.5, EASEINQUAD, 120);
		if (frame % 15 == 0) {
			CreateBulletGroup(BossPos, gamingColor, B_UNKO, BLEND_NOBLEND, 255, 1, 16, 16, 0, 0, 1.0f, 1.0f, 0, 0, 4, TAU, 1, 0, 0, 0, 0, 0.5, 20, EASEINCUBIC, 30);
		}
		screenRotateZ = sin(Rad(frame - Beat2Frame(240, 4, 77)) * 12) * Rad(15);
	}
	if (frame > Beat2Frame(240, 4, 93) && frame < Beat2Frame(240, 4, 109)) {
		BossPos = Vec2D(CENTER_X + sin(Rad(frame * 2)) * 50, CENTER_Y + sin(Rad(frame * 1.5) * 1.3) * 50);
		DrawRotaGraph(BossPos.x, BossPos.y, 1.0f, 0.0f, imgRes.EnemyGH[0], 1);
		CreateBulletGroup(BossPos, GetColorHSV(std::fmod(frame, 360), 1, 1), B_UNKO, BLEND_ADD, 255, 1, 24.0f, 24.0f, EASEINQUAD, 120, 1.5f, 1.5f, EASEINQUAD, 120, 4, TAU, 0, Rad(frame + sin(Rad(frame * 2 + sin(Rad(frame * 2)) * 20)) * 20), Rad(frame + 80 + sin(Rad(frame * 1.25)) * 20), EASEOUTQUAD, 240, -10.0f + sin(Rad(frame * 1.25)) * 2, 10.0f + sin(Rad(frame * 1.5)) * 1.5, EASEINQUAD, 120);
		if (frame % 2 == 0) {
			CreateBulletGroup(BossPos, Color(C_WHITE), B_UNKO, BLEND_NOBLEND, 255, 1, 24, 24, 0, 0, 1.0f, 1.0f, 0, 0, 48, Rad(240), 1, Rad(180), Rad(180), 0, 0, 15, 15, 0, 0);
		}
		if (frame % 15 == 0) {
			CreateBulletGroup(BossPos, gamingColor, B_UNKO, BLEND_NOBLEND, 255, 1, 16, 16, 0, 0, 1.0f, 1.0f, 0, 0, 4, TAU, 1, 0, 0, 0, 0, 0.5, 20, EASEINCUBIC, 30);
		}
		screenRotateZ = Rad(std::fmod(rng() / 100.0f, 30));
	}
	if (frame == Beat2Frame(240, 4, 109)) {
		screenRotateZ = 0;
	}
	if (frame > Beat2Frame(240, 4, 109)) {
		DrawBox(0, 0, 1920, 1080, GetColor(C_BLACK), 1);
		DrawRotaGraph(CENTER_X, CENTER_Y, 1.0f, Rad(std::fmod(rng() / 100.0f, 360)), imgRes.UIGH[2], 1);
	}
}