#include "DxLib.h"
#include "Game.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	// Windowモード設定
	ChangeWindowMode(Game::window_mode);

	// Window名設定
	SetMainWindowText(Game::title_text);

	// 画面サイズの設定
	SetGraphMode(Game::screen_width, Game::screen_height, Game::color_depth);

	// ゲーム中にウィンドウモードを切り替えてもグラフィックハンドルをリセットしない
	SetChangeScreenModeGraphicsSystemResetFlag(false);

	// ほかのウィンドウを選択していても動くようにする
	SetAlwaysRunFlag(false);

	// ウィンドウのサイズを変更可能にする
	SetWindowSizeChangeEnableFlag(true);

	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)		
	{
		// エラーが起きたら直ちに終了
		return -1;				
	}

	// ダブルバッファモード
	SetDrawScreen(DX_SCREEN_BACK);

	// 異常が起きた時に終了
	while (ProcessMessage() == 0)
	{
		LONGLONG time = GetNowHiPerformanceCount();

		// 画面のクリア
		ClearDrawScreen();

		// 裏画面を表画面を入れ替える
		ScreenFlip();

		// escキーを押したら終了する
		if (CheckHitKey(KEY_INPUT_ESCAPE))	break;
		
		// fpsを60に固定
		while (GetNowHiPerformanceCount() - time < 16667)
		{

		}
	}

	// ＤＸライブラリ使用の終了処理
	DxLib_End();				

	// ソフトの終了 
	return 0;					
}
