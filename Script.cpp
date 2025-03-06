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
		for (int i = 0; i < 4000; i++) {
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
			CreateBulletGroup(BossPos, gamingColor, B_MIDIAM, BLEND_NOBLEND, 255, 1, 32, 32, 0, 0, 1.0f, 1.0f, 0, 0, 16, TAU, 0, RandTMP, RandTMP, 0, 0, 10, 10, 0, 0);
		}
		if (frame % Beat2Frame(960, 4, 0.25f) == 0) {
			if (frame > 285 && frame < 300) {
				CreateBulletGroup(BossPos, gamingColor, B_MIDIAM, BLEND_NOBLEND, 255, 1, 32, 32, 0, 0, 1.0f, 1.0f, 0, 0, 24, TAU, 1, TAU / 48, TAU / 48, 0, 0, 20, 20, 0, 0);
			}
			if (frame > 765 && frame < 780) {
				CreateBulletGroup(BossPos, gamingColor, B_MIDIAM, BLEND_NOBLEND, 255, 1, 32, 32, 0, 0, 1.0f, 1.0f, 0, 0, 24, TAU, 1, TAU / 48, TAU / 48, 0, 0, 20, 20, 0, 0);
			}
		}
	}
	if (frame > Beat2Frame(240, 4, 17) && frame < Beat2Frame(240, 4, 48.75)) {
		BossPos = Vec2D(CENTER_X + sin(Rad(frame * 2)) * 50, CENTER_Y + sin(Rad(frame * 1.5) * 1.3) * 50);
		DrawRotaGraph(BossPos.x, BossPos.y, 1.0f, 0.0f, imgRes.EnemyGH[0], 1);
		CreateBulletGroup(BossPos, GetColorHSV(std::fmod(frame, 360), 1, 1), B_LIGHT, BLEND_ADD, 255, 1, 10.0f, 10.0f, EASEINQUAD, 120, 2.0f, 2.0f, EASEINQUAD, 120, 4, TAU, 0, Rad(frame + sin(Rad(frame * 2 + sin(Rad(frame * 2)) * 20)) * 20), Rad(frame + 80 + sin(Rad(frame * 1.25)) * 20), EASEOUTQUAD, 240, -10.0f + sin(Rad(frame * 1.25)) * 2, 10.0f + sin(Rad(frame * 1.5)) * 1.5, EASEINQUAD, 120);
		if (frame % 15 == 0) {
			CreateBulletGroup(BossPos, gamingColor, B_MIDIAM, BLEND_NOBLEND, 255, 1, 32, 32, 0, 0, 1.0f, 1.0f, 0, 0, 4, TAU, 1, 0, 0, 0, 0, 0.5, 20, EASEINCUBIC, 30);
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
		CreateBulletGroup(BossPos, Color(C_BLACK), B_MIDIAM, BLEND_NOBLEND, 255, 0, 32, 32, 0, 0, 1.0f, 1.0f, 0, 0, 128, TAU, 1, TAU / 128, TAU / 128, 0, 0, 25, 25, 0, 0);
	}
	if (frame > Beat2Frame(240, 4, 50) && frame < Beat2Frame(240, 4, 53.5)) {
		if (frame % 15 == 0) {
			RandTMP = std::fmod(rng() / 100.0f, 360);
			CreateBulletGroup(BossPos, Color(C_BLACK), B_NORMAL, BLEND_NOBLEND, 255, 1, 8, 8, 0, 0, 1.0f, 1.0f, 0, 0, 64, TAU, 0, RandTMP, RandTMP, 0, 0, 15, 3, EASEINCUBIC, 30);
		}
	}
	if (frame > Beat2Frame(240, 4, 109)) {
		DrawBox(0, 0, 1920, 1080, GetColor(C_BLACK), 1);
	}
}