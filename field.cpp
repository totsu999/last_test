
#include "field.h"
#include "myDirect3D.h"
#include "input.h"
#include "texture.h"
#include "debugproc.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

#define	VALUE_MOVE		(5.0f)							// 移動量
#define	VALUE_ROTATE	(D3DX_PI * 0.02f)				// 回転量

#define	FIELD_WIDTH		(100.0f)						// 地面の幅(X方向)
#define	FIELD_DEPTH		(100.0f)						// 地面の奥行(Z方向)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexField(LPDIRECT3DDEVICE9 pDevice);
HRESULT MakeVertexField2(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffField = NULL;	// 頂点バッファへのポインタ

D3DXMATRIX				g_mtxWorldField;		// ワールドマトリックス
D3DXVECTOR3				g_posField;				// 地面の位置
D3DXVECTOR3				g_rotField;				// 地面の向き(回転)
D3DXVECTOR3				g_sclField;				// 地面の大きさ(スケール)

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Field_Initialize(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	// 頂点情報の作成
	MakeVertexField(pDevice);
	MakeVertexField2(pDevice);

	// 位置・回転・スケールの初期設定
	g_posField = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotField = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_sclField = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void Field_Finalize(void)
{
	if(g_pVtxBuffField != NULL)
	{// 頂点バッファの開放
		g_pVtxBuffField->Release();
		g_pVtxBuffField = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void Field_Update(void)
{
	if (Keyboard_IsPress(DIK_A))
	{
		if (Keyboard_IsPress(DIK_W))
		{// 左奥移動
			g_posField.x += sinf(-D3DX_PI * 0.75f) * VALUE_MOVE;
			g_posField.z -= cosf(-D3DX_PI * 0.75f) * VALUE_MOVE;
		}
		else if (Keyboard_IsPress(DIK_S))
		{// 左手前移動
			g_posField.x += sinf(-D3DX_PI * 0.25f) * VALUE_MOVE;
			g_posField.z -= cosf(-D3DX_PI * 0.25f) * VALUE_MOVE;
		}
		else
		{// 左移動
			g_posField.x += sinf(-D3DX_PI * 0.50f) * VALUE_MOVE;
			g_posField.z -= cosf(-D3DX_PI * 0.50f) * VALUE_MOVE;
		}
	}
	else if (Keyboard_IsPress(DIK_D))
	{
		if (Keyboard_IsPress(DIK_W))
		{// 右奥移動
			g_posField.x += sinf(D3DX_PI * 0.75f) * VALUE_MOVE;
			g_posField.z -= cosf(D3DX_PI * 0.75f) * VALUE_MOVE;
		}
		else if (Keyboard_IsPress(DIK_S))
		{// 右手前移動
			g_posField.x += sinf(D3DX_PI * 0.25f) * VALUE_MOVE;
			g_posField.z -= cosf(D3DX_PI * 0.25f) * VALUE_MOVE;
		}
		else
		{// 右移動
			g_posField.x += sinf(D3DX_PI * 0.50f) * VALUE_MOVE;
			g_posField.z -= cosf(D3DX_PI * 0.50f) * VALUE_MOVE;
		}
	}
	else if (Keyboard_IsPress(DIK_W))
	{// 奥移動
		g_posField.x += sinf(D3DX_PI * 1.0f) * VALUE_MOVE;
		g_posField.z -= cosf(D3DX_PI * 1.0f) * VALUE_MOVE;
	}
	else if (Keyboard_IsPress(DIK_S))
	{// 手前移動
		g_posField.x += sinf(D3DX_PI * 0.0f) * VALUE_MOVE;
		g_posField.z -= cosf(D3DX_PI * 0.0f) * VALUE_MOVE;
	}

#if 1
	if (Keyboard_IsPress(DIK_Q))
	{// Y軸左回転
		g_rotField.y -= VALUE_ROTATE;
		if(g_rotField.y > D3DX_PI)
		{
			g_rotField.y -= D3DX_PI * 2.0f;
		}
		if(g_rotField.y < -D3DX_PI)
		{
			g_rotField.y += D3DX_PI * 2.0f;
		}
	}
	if (Keyboard_IsPress(DIK_E))
	{// Y軸右回転
		g_rotField.y += VALUE_ROTATE;
		if(g_rotField.y > D3DX_PI)
		{
			g_rotField.y -= D3DX_PI * 2.0f;
		}
		if(g_rotField.y < -D3DX_PI)
		{
			g_rotField.y += D3DX_PI * 2.0f;
		}
	}
#endif

#if 1
	if (Keyboard_IsPress(DIK_UP))
	{// X軸右回転
		g_rotField.x += VALUE_ROTATE;
		if(g_rotField.x > D3DX_PI)
		{
			g_rotField.x -= D3DX_PI * 2.0f;
		}
		if(g_rotField.x < -D3DX_PI)
		{
			g_rotField.x += D3DX_PI * 2.0f;
		}
	}
	if (Keyboard_IsPress(DIK_DOWN))
	{// X軸左回転
		g_rotField.x -= VALUE_ROTATE;
		if(g_rotField.x > D3DX_PI)
		{
			g_rotField.x -= D3DX_PI * 2.0f;
		}
		if(g_rotField.x < -D3DX_PI)
		{
			g_rotField.x += D3DX_PI * 2.0f;
		}
	}
#endif

#if 1
	if (Keyboard_IsPress(DIK_LEFT))
	{// Z軸右回転
		g_rotField.z += VALUE_ROTATE;
		if(g_rotField.z > D3DX_PI)
		{
			g_rotField.z -= D3DX_PI * 2.0f;
		}
		if(g_rotField.z < -D3DX_PI)
		{
			g_rotField.z += D3DX_PI * 2.0f;
		}
	}
	if (Keyboard_IsPress(DIK_RIGHT))
	{// Z軸左回転
		g_rotField.z -= VALUE_ROTATE;
		if(g_rotField.z > D3DX_PI)
		{
			g_rotField.z -= D3DX_PI * 2.0f;
		}
		if(g_rotField.z < -D3DX_PI)
		{
			g_rotField.z += D3DX_PI * 2.0f;
		}
	}
#endif

	if (Keyboard_IsPress(DIK_RETURN))
	{// リセット
		g_posField.x = 0.0f;
		g_posField.y = 0.0f;
		g_posField.z = 0.0f;

		g_rotField.x = 0.0f;
		g_rotField.y = 0.0f;
		g_rotField.z = 0.0f;
	}

	//光が差す方向
	D3DXVECTOR3 light;
	light.x = 0.0f;
	light.y = -1.0f;
	light.z = 0.0f;
	
	{
		VERTEX_3D *pVtx;

		//頂点データの範囲をロックし、頂点バッファへ
		g_pVtxBuffField->Lock(0, 0, (void**)&pVtx, 0);

		//法線ベクトルとライトの方向で内積を取る
		//float bright = D3DXVec3Dot(&pVtx[0].nor,&light);

	

		g_pVtxBuffField->Unlock();
	}

	DebugProc_Print((char *)"*** ３Ｄポリゴン操作 ***\n");
	DebugProc_Print((char *)"位置 [%f : %f : %f]\n", g_posField.x, g_posField.y, g_posField.z);
	DebugProc_Print((char *)"前移動 : Ｗ\n");
	DebugProc_Print((char *)"後移動 : Ｓ\n");
	DebugProc_Print((char *)"左移動 : Ａ\n");
	DebugProc_Print((char *)"右移動 : Ｄ\n");
	DebugProc_Print((char *)"\n");

	DebugProc_Print((char *)"向き [%f : %f : %f]\n", g_rotField.x, g_rotField.y, g_rotField.z);
	DebugProc_Print((char *)"X軸回転 : ↑ / ↓\n");
	DebugProc_Print((char *)"Y軸回転 : Ｑ / Ｅ\n");
	DebugProc_Print((char *)"Z軸回転 : ← / →\n");
	DebugProc_Print((char *)"\n");

	DebugProc_Print((char *)"位置・向きリセット : ENTER\n");
}

//=============================================================================
// 描画処理
//=============================================================================
void Field_Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	D3DXMatrixIdentity(&g_mtxWorldField);

	D3DXMatrixScaling(&mtxScl, g_sclField.x, g_sclField.y, g_sclField.z);
	D3DXMatrixMultiply(&g_mtxWorldField, &g_mtxWorldField, &mtxScl);

	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotField.y, g_rotField.x, g_rotField.z);
	D3DXMatrixMultiply(&g_mtxWorldField, &g_mtxWorldField, &mtxRot);

	D3DXMatrixTranslation(&mtxTranslate, g_posField.x, g_posField.y, g_posField.z);
	D3DXMatrixMultiply(&g_mtxWorldField, &g_mtxWorldField, &mtxTranslate);

	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldField);

	pDevice->SetStreamSource(0, g_pVtxBuffField, 0, sizeof(VERTEX_3D));

	pDevice->SetFVF(FVF_VERTEX_3D);

	pDevice->SetTexture(0, Texture_GetTexture(TEXTURE_INDEX_FIELD01));

	pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, NUM_POLYGON);
}

void Field_Draw2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	D3DXMatrixIdentity(&g_mtxWorldField);

	D3DXMatrixScaling(&mtxScl, g_sclField.x, g_sclField.y, g_sclField.z);
	D3DXMatrixMultiply(&g_mtxWorldField, &g_mtxWorldField, &mtxScl);

	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotField.y, g_rotField.x, g_rotField.z);
	D3DXMatrixMultiply(&g_mtxWorldField, &g_mtxWorldField, &mtxRot);

	D3DXMatrixTranslation(&mtxTranslate, g_posField.x, g_posField.y, g_posField.z);
	D3DXMatrixMultiply(&g_mtxWorldField, &g_mtxWorldField, &mtxTranslate);

	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldField);

	pDevice->SetStreamSource(0, g_pVtxBuffField, 0, sizeof(VERTEX_3D));

	pDevice->SetFVF(FVF_VERTEX_3D);

	pDevice->SetTexture(0, Texture_GetTexture(TEXTURE_INDEX_FIELD01));

	pDevice->DrawPrimitive(D3DPT_LINELIST, 0, NUM_POLYGON2);
}
//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexField(LPDIRECT3DDEVICE9 pDevice)
{
	//if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D)*NUM_VERTEX,
	//	D3DUSAGE_WRITEONLY,
	//	FVF_VERTEX_3D,
	//	D3DPOOL_MANAGED,
	//	&g_pVtxBuffField,
	//	NULL)))
	//{
	//	return E_FAIL;
	//}
	//{
	//	VERTEX_3D *pVtx;

	//	g_pVtxBuffField->Lock(0, 0, (void**)&pVtx, 0);

	//	//光が差す方向
	//		D3DXVECTOR3 light;
	//		light.x = 0.0f;
	//		light.y = -1.0f;
	//		light.z = 0.0f;

	//	{
	//		pVtx[0].pos = D3DXVECTOR3(-FIELD_WIDTH, FIELD_DEPTH, FIELD_DEPTH);
	//		pVtx[1].pos = D3DXVECTOR3(FIELD_WIDTH, FIELD_DEPTH, FIELD_DEPTH);
	//		pVtx[2].pos = D3DXVECTOR3(-FIELD_WIDTH, FIELD_DEPTH, -FIELD_DEPTH);
	//		pVtx[3].pos = D3DXVECTOR3(FIELD_WIDTH, FIELD_DEPTH, FIELD_DEPTH);
	//		pVtx[4].pos = D3DXVECTOR3(FIELD_WIDTH, FIELD_DEPTH, -FIELD_DEPTH);
	//		pVtx[5].pos = D3DXVECTOR3(-FIELD_WIDTH, FIELD_DEPTH, -FIELD_DEPTH);

	//		pVtx[6].pos = D3DXVECTOR3(FIELD_WIDTH, FIELD_DEPTH, FIELD_DEPTH);
	//		pVtx[7].pos = D3DXVECTOR3(FIELD_WIDTH, -FIELD_DEPTH , FIELD_DEPTH);
	//		pVtx[8].pos = D3DXVECTOR3(FIELD_WIDTH, FIELD_DEPTH, -FIELD_DEPTH);
	//		pVtx[9].pos = D3DXVECTOR3(FIELD_WIDTH, -FIELD_DEPTH , FIELD_DEPTH);
	//		pVtx[10].pos = D3DXVECTOR3(FIELD_WIDTH, -FIELD_DEPTH , -FIELD_DEPTH);
	//		pVtx[11].pos = D3DXVECTOR3(FIELD_WIDTH, FIELD_DEPTH, -FIELD_DEPTH);

	//		pVtx[12].pos = D3DXVECTOR3(FIELD_WIDTH, -FIELD_DEPTH , FIELD_DEPTH);
	//		pVtx[13].pos = D3DXVECTOR3(-FIELD_WIDTH, -FIELD_DEPTH , FIELD_DEPTH);
	//		pVtx[14].pos = D3DXVECTOR3(FIELD_WIDTH, -FIELD_DEPTH , -FIELD_DEPTH);
	//		pVtx[15].pos = D3DXVECTOR3(-FIELD_WIDTH, -FIELD_DEPTH , FIELD_DEPTH);
	//		pVtx[16].pos = D3DXVECTOR3(-FIELD_WIDTH, -FIELD_DEPTH , -FIELD_DEPTH);
	//		pVtx[17].pos = D3DXVECTOR3(FIELD_WIDTH, -FIELD_DEPTH , -FIELD_DEPTH);

	//		pVtx[18].pos = D3DXVECTOR3(-FIELD_WIDTH, -FIELD_DEPTH , FIELD_DEPTH);
	//		pVtx[19].pos = D3DXVECTOR3(-FIELD_WIDTH, FIELD_DEPTH, FIELD_DEPTH);
	//		pVtx[20].pos = D3DXVECTOR3(-FIELD_WIDTH, -FIELD_DEPTH , -FIELD_DEPTH);
	//		pVtx[21].pos = D3DXVECTOR3(-FIELD_WIDTH, FIELD_DEPTH, FIELD_DEPTH);
	//		pVtx[22].pos = D3DXVECTOR3(-FIELD_WIDTH, FIELD_DEPTH, -FIELD_DEPTH);
	//		pVtx[23].pos = D3DXVECTOR3(-FIELD_WIDTH, -FIELD_DEPTH , -FIELD_DEPTH);

	//		pVtx[24].pos = D3DXVECTOR3(-FIELD_WIDTH, -FIELD_DEPTH , FIELD_DEPTH);
	//		pVtx[25].pos = D3DXVECTOR3(FIELD_WIDTH, -FIELD_DEPTH , FIELD_DEPTH);
	//		pVtx[26].pos = D3DXVECTOR3(-FIELD_WIDTH, FIELD_DEPTH, FIELD_DEPTH);
	//		pVtx[27].pos = D3DXVECTOR3(FIELD_WIDTH, -FIELD_DEPTH , FIELD_DEPTH);
	//		pVtx[28].pos = D3DXVECTOR3(FIELD_WIDTH, FIELD_DEPTH, FIELD_DEPTH);
	//		pVtx[29].pos = D3DXVECTOR3(-FIELD_WIDTH, FIELD_DEPTH, FIELD_DEPTH);

	//		pVtx[30].pos = D3DXVECTOR3(-FIELD_WIDTH, FIELD_DEPTH, -FIELD_DEPTH);
	//		pVtx[31].pos = D3DXVECTOR3(FIELD_WIDTH, FIELD_DEPTH, -FIELD_DEPTH);
	//		pVtx[32].pos = D3DXVECTOR3(-FIELD_WIDTH, -FIELD_DEPTH , -FIELD_DEPTH);
	//		pVtx[33].pos = D3DXVECTOR3(FIELD_WIDTH, FIELD_DEPTH, -FIELD_DEPTH);
	//		pVtx[34].pos = D3DXVECTOR3(FIELD_WIDTH, -FIELD_DEPTH , -FIELD_DEPTH);
	//		pVtx[35].pos = D3DXVECTOR3(-FIELD_WIDTH, -FIELD_DEPTH , -FIELD_DEPTH);
	//	}

	//
	//	{
	//		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//		pVtx[4].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//		pVtx[5].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//		pVtx[6].nor = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	//		pVtx[7].nor = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	//		pVtx[8].nor = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	//		pVtx[9].nor = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	//		pVtx[10].nor = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	//		pVtx[11].nor = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

	//		pVtx[12].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	//		pVtx[13].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	//		pVtx[14].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	//		pVtx[15].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	//		pVtx[16].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	//		pVtx[17].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);

	//		pVtx[18].nor = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
	//		pVtx[19].nor = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
	//		pVtx[20].nor = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
	//		pVtx[21].nor = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
	//		pVtx[22].nor = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
	//		pVtx[23].nor = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);

	//		pVtx[24].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	//		pVtx[25].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	//		pVtx[26].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	//		pVtx[27].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	//		pVtx[28].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	//		pVtx[29].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	//		pVtx[30].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	//		pVtx[31].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	//		pVtx[32].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	//		pVtx[33].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	//		pVtx[34].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	//		pVtx[35].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	//	}

	//	{
	//		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//		pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//		pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//		pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//		pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//		pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//		pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//		pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//		pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//		pVtx[12].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//		pVtx[13].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//		pVtx[14].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//		pVtx[15].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//		pVtx[16].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//		pVtx[17].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//		pVtx[18].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//		pVtx[19].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//		pVtx[20].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//		pVtx[21].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//		pVtx[22].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//		pVtx[23].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//		pVtx[24].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//		pVtx[25].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//		pVtx[26].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//		pVtx[27].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//		pVtx[28].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//		pVtx[29].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//		pVtx[30].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//		pVtx[31].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//		pVtx[32].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//		pVtx[33].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//		pVtx[34].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//		pVtx[35].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//	}

	//	{
	//		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);
	//		pVtx[4].tex = D3DXVECTOR2(1.0f, 1.0f);
	//		pVtx[5].tex = D3DXVECTOR2(0.0f, 1.0f);

	//		pVtx[6].tex = D3DXVECTOR2(0.0f, 0.0f);
	//		pVtx[7].tex = D3DXVECTOR2(1.0f, 0.0f);
	//		pVtx[8].tex = D3DXVECTOR2(0.0f, 1.0f);
	//		pVtx[9].tex = D3DXVECTOR2(1.0f, 0.0f);
	//		pVtx[10].tex = D3DXVECTOR2(1.0f, 1.0f);
	//		pVtx[11].tex = D3DXVECTOR2(0.0f, 1.0f);

	//		pVtx[12].tex = D3DXVECTOR2(0.0f, 0.0f);
	//		pVtx[13].tex = D3DXVECTOR2(1.0f, 0.0f);
	//		pVtx[14].tex = D3DXVECTOR2(0.0f, 1.0f);
	//		pVtx[15].tex = D3DXVECTOR2(1.0f, 0.0f);
	//		pVtx[16].tex = D3DXVECTOR2(1.0f, 1.0f);
	//		pVtx[17].tex = D3DXVECTOR2(0.0f, 1.0f);

	//		pVtx[18].tex = D3DXVECTOR2(0.0f, 0.0f);
	//		pVtx[19].tex = D3DXVECTOR2(1.0f, 0.0f);
	//		pVtx[20].tex = D3DXVECTOR2(0.0f, 1.0f);
	//		pVtx[21].tex = D3DXVECTOR2(1.0f, 0.0f);
	//		pVtx[22].tex = D3DXVECTOR2(1.0f, 1.0f);
	//		pVtx[23].tex = D3DXVECTOR2(0.0f, 1.0f);

	//		pVtx[24].tex = D3DXVECTOR2(0.0f, 0.0f);
	//		pVtx[25].tex = D3DXVECTOR2(1.0f, 0.0f);
	//		pVtx[26].tex = D3DXVECTOR2(0.0f, 1.0f);
	//		pVtx[27].tex = D3DXVECTOR2(1.0f, 0.0f);
	//		pVtx[28].tex = D3DXVECTOR2(1.0f, 1.0f);
	//		pVtx[29].tex = D3DXVECTOR2(0.0f, 1.0f);

	//		pVtx[30].tex = D3DXVECTOR2(0.0f, 0.0f);
	//		pVtx[31].tex = D3DXVECTOR2(1.0f, 0.0f);
	//		pVtx[32].tex = D3DXVECTOR2(0.0f, 1.0f);
	//		pVtx[33].tex = D3DXVECTOR2(1.0f, 0.0f);
	//		pVtx[34].tex = D3DXVECTOR2(1.0f, 1.0f);
	//		pVtx[35].tex = D3DXVECTOR2(0.0f, 1.0f);

	//	}


	//	g_pVtxBuffField->Unlock();
	//}
	return S_OK;
}

HRESULT MakeVertexField2(LPDIRECT3DDEVICE9 pDevice)
{
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D)*NUM_VERTEX2,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffField,
		NULL)))
	{
		return E_FAIL;
	}
	{
		VERTEX_3D *pVtx;

		g_pVtxBuffField->Lock(0, 0, (void**)&pVtx, 0);

		{
			for (int i = 0; i < 12; i+=2)
			{
				pVtx[i].pos = D3DXVECTOR3(-FIELD_WIDTH+i*20, FIELD_DEPTH, FIELD_DEPTH);
				pVtx[i+1].pos = D3DXVECTOR3(-FIELD_WIDTH+i*20, FIELD_DEPTH, -FIELD_DEPTH);
			}
			
			
		}

		/*for (int i=0; i < 36; i++)
		{
		pVtx[i].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		}*/
		{
			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[4].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[5].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			pVtx[6].nor = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
			pVtx[7].nor = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
			pVtx[8].nor = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
			pVtx[9].nor = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
			pVtx[10].nor = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
			pVtx[11].nor = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

			pVtx[12].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
			pVtx[13].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
			pVtx[14].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
			pVtx[15].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
			pVtx[16].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
			pVtx[17].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);

			pVtx[18].nor = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
			pVtx[19].nor = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
			pVtx[20].nor = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
			pVtx[21].nor = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
			pVtx[22].nor = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
			pVtx[23].nor = D3DXVECTOR3(1.0f, 1.0f, 0.0f);

			pVtx[24].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
			pVtx[25].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
			pVtx[26].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
			pVtx[27].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
			pVtx[28].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
			pVtx[29].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

			pVtx[30].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[31].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[32].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[33].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[34].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[35].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		}

		{
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			pVtx[12].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[13].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[14].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[15].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[16].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[17].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			pVtx[18].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[19].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[20].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[21].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[22].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[23].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			pVtx[24].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[25].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[26].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[27].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[28].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[29].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			pVtx[30].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[31].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[32].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[33].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[34].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[35].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}

		{
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[4].tex = D3DXVECTOR2(1.0f, 1.0f);
			pVtx[5].tex = D3DXVECTOR2(0.0f, 1.0f);

			pVtx[6].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[7].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[8].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[9].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[10].tex = D3DXVECTOR2(1.0f, 1.0f);
			pVtx[11].tex = D3DXVECTOR2(0.0f, 1.0f);

			pVtx[12].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[13].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[14].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[15].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[16].tex = D3DXVECTOR2(1.0f, 1.0f);
			pVtx[17].tex = D3DXVECTOR2(0.0f, 1.0f);

			pVtx[18].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[19].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[20].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[21].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[22].tex = D3DXVECTOR2(1.0f, 1.0f);
			pVtx[23].tex = D3DXVECTOR2(0.0f, 1.0f);

			pVtx[24].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[25].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[26].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[27].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[28].tex = D3DXVECTOR2(1.0f, 1.0f);
			pVtx[29].tex = D3DXVECTOR2(0.0f, 1.0f);

			pVtx[30].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[31].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[32].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[33].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[34].tex = D3DXVECTOR2(1.0f, 1.0f);
			pVtx[35].tex = D3DXVECTOR2(0.0f, 1.0f);

		}


		g_pVtxBuffField->Unlock();
	}
	return S_OK;
}