#include <Novice.h>
#include "Matrix.h"
#include <cstring>

const char kWindowTitle[] = "GC2B_14_ハラ_アイ";
static const int kRowHeight = 20;
static const int kColumnWidth = 60;

void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix)
{
    for (int row = 0; row < 4; ++row)
    {
        for (int column = 0; column < 4; ++column)
        {
            Novice::ScreenPrintf(
                x + column * kColumnWidth, y + row * kRowHeight,
                "%6.02f", matrix.m[row][column]);
        }
    }
}

void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label)
{
    Novice::ScreenPrintf(x, y, "%.02f", vector.x);
    Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", vector.y);
    Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%.02f", vector.z);
    Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label);
}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

    // ライブラリの初期化
    Novice::Initialize(kWindowTitle, 1280, 720);

    // キー入力結果を受け取る箱
    char keys[256] = { 0 };
    char preKeys[256] = { 0 };

    // 平行移動ベクトルと拡大縮小ベクトルを定義
    Vector3 translation(4.1f, 2.6f, 0.8f);
    Vector3 scale(1.5f, 5.2f, 7.3f);

    // 行列を作成
    Matrix4x4 translateMatrix = MakeTranslateMatrix(translation);
    Matrix4x4 scaleMatrix = MakeScaleMatrix(scale);

    Vector3 point{ 2.3f,3.8f,1.4f };
    Matrix4x4 transformMatrix = 
    {
        1.0f, 2.0f, 3.0f, 4.0f,
        3.0f, 1.0f, 1.0f, 2.0f,
        1.0f, 4.0f, 2.0f, 3.0f,
        2.0f, 2.0f, 1.0f, 3.0f
    };

    Vector3 transformed = Transform(point, transformMatrix);

    // ウィンドウの×ボタンが押されるまでループ
    while (Novice::ProcessMessage() == 0) {
        // フレームの開始
        Novice::BeginFrame();

        // キー入力を受け取る
        memcpy(preKeys, keys, 256);
        Novice::GetHitKeyStateAll(keys);

        ///
        /// ↓更新処理ここから
        ///
       
        ///
        /// ↑更新処理ここまで
        ///

        ///
        /// ↓描画処理ここから
        ///

        VectorScreenPrintf(0, 0, transformed, "transformed");
        MatrixScreenPrintf(0, 20, translateMatrix);
        MatrixScreenPrintf(0, kRowHeight * 5 + 20, scaleMatrix);

        ///
        /// ↑描画処理ここまで
        ///

        // フレームの終了
        Novice::EndFrame();

        // ESCキーが押されたらループを抜ける
        if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
            break;
        }
    }

    // ライブラリの終了
    Novice::Finalize();
    return 0;
}
