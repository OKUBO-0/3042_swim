#include <KamataEngine.h>

using namespace KamataEngine;
using namespace MathUtility;

void WorldTransform::UpdateMatrix() {
    // ==============================
    // スケーリング行列
    // ==============================
    Matrix4x4 matScale = MakeScaleMatrix(scale_);

    // ==============================
    // 回転行列（X, Y, Z の順に作成）
    // ==============================
    Matrix4x4 matRotX = MakeRotateXMatrix(rotation_.x);
    Matrix4x4 matRotY = MakeRotateYMatrix(rotation_.y);
    Matrix4x4 matRotZ = MakeRotateZMatrix(rotation_.z);

    // 回転行列の合成（Z * X * Y の順）
    Matrix4x4 matRot = matRotZ * matRotX * matRotY;

    // ==============================
    // 平行移動行列
    // ==============================
    Matrix4x4 matTrans = MakeTranslateMatrix(translation_);

    // ==============================
    // ワールド行列の合成
    // スケーリング -> 回転 -> 平行移動
    // ==============================
    matWorld_ = matScale * matRot * matTrans;

    // ==============================
    // 定数バッファに転送
    // ==============================
    TransferMatrix();
}