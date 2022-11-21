#include "GameScene.h"
#include <cassert>

using namespace DirectX;

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	delete spriteBG;
	delete particleMan;
	delete sprite1;
	delete sprite2;
}

void GameScene::Initialize(DirectXCommon* dxCommon, Input* input)
{
	// nullptrチェック
	assert(dxCommon);
	assert(input);

	this->dxCommon = dxCommon;
	this->input = input;

	// デバッグテキスト用テクスチャ読み込み
	Sprite::LoadTexture(debugTextTexNumber, L"Resources/debugfont.png");
	// デバッグテキスト初期化
	debugText.Initialize(debugTextTexNumber);

	// テクスチャ読み込み
	Sprite::LoadTexture(1, L"Resources/b.jpg");

	Sprite::LoadTexture(2, L"Resources/texture.png");

	sprite1 = Sprite::Create(2, { 0,0 });
	sprite2 = Sprite::Create(2, { 500,500 }, { 1,0,0,1 }, { 0,0 }, false, true);

	// 背景スプライト生成
	spriteBG = Sprite::Create(1, { 0.0f,0.0f });
	// 3Dオブジェクト生成
	particleMan = ParticleManager::Create();
	particleMan->Update();

	ParticleManager::CameraMoveEyeVector({ 0.0f,30.0f,0.0f });

	object3d = Object3d::Create();
	BilbordObj2 = Object3d::Create();
	BilbordObj2->SetPosition(XMFLOAT3(20, 0, 0));
	BilbordObj3 = Object3d::Create();
	BilbordObj3->SetPosition(XMFLOAT3(-20, 0, 0));
}

void GameScene::Update()
{
	
	if (input->TriggerKey(DIK_SPACE)) {
		const float md_pos = 30.0f;
		pos3.x = (float)rand() / RAND_MAX * md_pos - md_pos / 2.0f;
		pos3.y = (float)rand() / RAND_MAX * md_pos - md_pos / 2.0f;
		pos3.z = (float)rand() / RAND_MAX * md_pos - md_pos / 2.0f;
		isPar = true;
	}

	if (input->TriggerKey(DIK_1)) {
		state = 1;
	}
	if (input->TriggerKey(DIK_2)) {
		state = 2;
	}
	if (input->TriggerKey(DIK_3)) {
		state = 3;
	}
	if (input->TriggerKey(DIK_4)) {
		state = 4;
	}
	if (input->TriggerKey(DIK_5)) {
		state = 5;
	}

	// カメラ移動
	if (input->PushKey(DIK_W) || input->PushKey(DIK_S) || input->PushKey(DIK_D) || input->PushKey(DIK_A))
	{
		if (state == 2 || state == 5) {
			if (input->PushKey(DIK_W)) { ParticleManager::CameraMoveEyeVector({ 0.0f,+1.0f,0.0f }); }
			else if (input->PushKey(DIK_S)) { ParticleManager::CameraMoveEyeVector({ 0.0f,-1.0f,0.0f }); }
			if (input->PushKey(DIK_D)) { ParticleManager::CameraMoveEyeVector({ +1.0f,0.0f,0.0f }); }
			else if (input->PushKey(DIK_A)) { ParticleManager::CameraMoveEyeVector({ -1.0f,0.0f,0.0f }); }
		}
		
		if (state == 1 || state == 5) {
			if (input->PushKey(DIK_W)) { Object3d::CameraMoveEyeVector({ 0.0f,+1.0f,0.0f }); }
			else if (input->PushKey(DIK_S)) { Object3d::CameraMoveEyeVector({ 0.0f,-1.0f,0.0f }); }
			if (input->PushKey(DIK_D)) { Object3d::CameraMoveEyeVector({ +1.0f,0.0f,0.0f }); }
			else if (input->PushKey(DIK_A)) { Object3d::CameraMoveEyeVector({ -1.0f,0.0f,0.0f }); }
		}	
	}

	if (state == 2 || state == 5) {
		for (int i = 0; i < 3; i++) {
			const float md_pos = 20.0f;

			pos.x = (float)rand() / RAND_MAX * md_pos - md_pos / 2.0f;
			pos.y = (float)rand() / RAND_MAX * md_pos - md_pos / 2.0f;
			pos.z = (float)rand() / RAND_MAX * md_pos - md_pos / 2.0f;

			const float md_vel = 0.1f;
			XMFLOAT3 vel{};
			vel.x = -0.1f;
			vel.z = -0.1f;

			XMFLOAT3 acc{};
			const float md_acc = 0.001f;
			acc.y = -(float)rand() / RAND_MAX * md_acc;

			particleMan->Add(60, pos, vel, acc, 1.0f, 0.0f);
		}
	}
	
	if (state == 3 || state == 5) {
		for (int i = 0; i < 3; i++) {
			const float md_pos = 20.0f;
			if (input->PushKey(DIK_UP)) { pos2.z += 0.05f; }
			else if (input->PushKey(DIK_DOWN)) { pos2.z -= 0.05f; }
			if (input->PushKey(DIK_RIGHT)) { pos2.x += 0.05f; }
			else if (input->PushKey(DIK_LEFT)) { pos2.x -= 0.05f; }

			const float md_vel = 0.1f;
			XMFLOAT3 vel2{};
			vel2.x = (float)rand() / RAND_MAX * md_vel - md_vel / 2.0f;
			vel2.y = (float)rand() / RAND_MAX * md_vel - md_vel / 2.0f;
			vel2.z = (float)rand() / RAND_MAX * md_vel - md_vel / 2.0f;
			XMFLOAT3 acc2{};
			const float md_acc = 0.001f;
			acc2.y = -(float)rand() / RAND_MAX * md_acc;

			particleMan->Add(60, pos2, vel2, acc2, 1.0f, 0.0f);
		}
	}
	
	if (state == 4 || state == 5) {

		if (isPar == true){

			for (int i = 0; i < 30; i++) {
				const float md_vel = 0.5f;
				XMFLOAT3 vel3{};
				vel3.x = (float)rand() / RAND_MAX * md_vel - md_vel / 2.0f;
				vel3.y = (float)rand() / RAND_MAX * md_vel - md_vel / 2.0f;
				vel3.z = (float)rand() / RAND_MAX * md_vel - md_vel / 2.0f;
				XMFLOAT3 acc3{};
				const float md_acc = 0.005f;
				acc3.y = -(float)rand() / RAND_MAX * md_acc;

				particleMan->Add(60, pos3, vel3, acc3, 1.0f, 0.0f);
			}


			isPar = false;
		}
	}

	particleMan->Update();
	object3d->Update(1);
	BilbordObj2->Update(0);
	BilbordObj3->Update(0);
}

void GameScene::Draw()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(cmdList);
	// 背景スプライト描画
	spriteBG->Draw();

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	ParticleManager::PreDraw(cmdList);

	// 3Dオブクジェクトの描画
	particleMan->Draw();

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// 3Dオブジェクト描画後処理
	ParticleManager::PostDraw();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Object3d::PreDraw(cmdList);

	// 3Dオブクジェクトの描画
	if (state == 1 || state == 5) {
		object3d->Draw();
		BilbordObj2->Draw();
		BilbordObj3->Draw();
	}

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// 3Dオブジェクト描画後処理
	Object3d::PostDraw();
#pragma endregion


#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(cmdList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// デバッグテキストの描画
	debugText.DrawAll(cmdList);

	// スプライト描画後処理
	Sprite::PostDraw();
#pragma endregion
}
