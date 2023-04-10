#include "DxLib.h"
#include "Game.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	// Window���[�h�ݒ�
	ChangeWindowMode(Game::window_mode);

	// Window���ݒ�
	SetMainWindowText(Game::title_text);

	// ��ʃT�C�Y�̐ݒ�
	SetGraphMode(Game::screen_width, Game::screen_height, Game::color_depth);

	// �Q�[�����ɃE�B���h�E���[�h��؂�ւ��Ă��O���t�B�b�N�n���h�������Z�b�g���Ȃ�
	SetChangeScreenModeGraphicsSystemResetFlag(false);

	// �ق��̃E�B���h�E��I�����Ă��Ă������悤�ɂ���
	SetAlwaysRunFlag(false);

	// �E�B���h�E�̃T�C�Y��ύX�\�ɂ���
	SetWindowSizeChangeEnableFlag(true);

	// �c�w���C�u��������������
	if (DxLib_Init() == -1)		
	{
		// �G���[���N�����璼���ɏI��
		return -1;				
	}

	// �_�u���o�b�t�@���[�h
	SetDrawScreen(DX_SCREEN_BACK);

	// �ُ킪�N�������ɏI��
	while (ProcessMessage() == 0)
	{
		LONGLONG time = GetNowHiPerformanceCount();

		// ��ʂ̃N���A
		ClearDrawScreen();

		// ����ʂ�\��ʂ����ւ���
		ScreenFlip();

		// esc�L�[����������I������
		if (CheckHitKey(KEY_INPUT_ESCAPE))	break;
		
		// fps��60�ɌŒ�
		while (GetNowHiPerformanceCount() - time < 16667)
		{

		}
	}

	// �c�w���C�u�����g�p�̏I������
	DxLib_End();				

	// �\�t�g�̏I�� 
	return 0;					
}
