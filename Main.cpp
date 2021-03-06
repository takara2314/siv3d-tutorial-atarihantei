#include <Siv3D.hpp>

void Main()
{
	Scene::SetBackground(ColorF(0, 0, 0));
	// https://pipoya.net/sozai/assets/map-chip_tileset32/
	Texture forestTile(U"map.png");
	// https://github.com/lriki/Siv3D-PixelArt
	Texture siv3d_kun(U"Siv3D-kun.png");
	const Font font(50);
	Window::Resize(512, 512);

	// マップタイル配列 (3次元配列)
	const std::vector<std::vector<std::vector<int>>> mapData = {
		// 1次レイヤー (地面など)
		{
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 4, 1, 1, 1, 1, 1 },
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 4, 1, 1, 1, 1, 1 },
			{ 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 },
			{ 1, 1, 1, 562, 562, 562, 562, 562, 562, 4, 4, 1, 1, 1, 1, 1 },
			{ 1, 1, 1, 570, 570, 570, 570, 570, 570, 4, 4, 1, 1, 1, 1, 1 },
			{ 1, 1, 1, 578, 578, 578, 578, 578, 578, 4, 4, 1, 1, 1, 1, 1 },
			{ 1, 1, 1, 586, 586, 586, 586, 586, 586, 4, 4, 1, 1, 1, 1, 1 },
			{ 1, 1, 1, 529, 529, 529, 529, 529, 529, 4, 4, 1, 1, 1, 1, 1 },
			{ 1, 1, 1, 537, 537, 537, 537, 537, 537, 4, 4, 1, 1, 1, 1, 1 },
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 4, 1, 1, 1, 1, 1 },
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 4, 1, 1, 1, 1, 1 },
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 4, 1, 1, 1, 1, 1 },
			{ 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 },
			{ 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 },
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 4, 1, 1, 1, 1, 1 },
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 4, 1, 1, 1, 1, 1 }
		},
		// 2次レイヤー (装飾物など)
		{
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 153, 154, 155, 156, 0 },
			{ 0, 0, 0, 0, 189, 185, 185, 185, 181, 0, 0, 169, 170, 171, 164, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 863, 0, 863, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 657, 0, 594, 641, 642, 594, 0, 0, 0, 0, 863, 0, 863, 0 },
			{ 0, 0, 0, 0, 602, 649, 650, 602, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 863, 0, 863, 0 },
			{ 0, 0, 55, 55, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 53, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 53, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 56, 56, 0, 0, 0, 0, 53, 53, 0, 0, 0, 0, 55, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 55, 0 }
		},
		// 当たり判定
		{
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
			{ 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0 },
			{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0 },
			{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
		}
	};

	// 初期地点
	double x = 256;
	double y = 300;

	while (System::Update())
	{
		// 移動させる量
		const double delta = 200 * Scene::DeltaTime();

		for (int i = 0; i < mapData.size(); ++i)
		{
			// 当たり判定の配列に到達したら終了
			if (i == 2)
			{
				break;
			}
			for (int j = 0; j < mapData[i].size(); ++j)
			{
				for (int k = 0; k < mapData[i][j].size(); ++k)
				{
					// 指定されたタイル番号が0以外なら
					if (mapData[i][j][k] != 0)
					{
						forestTile(
							((mapData[i][j][k] - 1) % 8) * 32,
							static_cast<int>(mapData[i][j][k] / 8) * 32,
							32, 32
						).draw(k * 32, j * 32);
					}
				}
			}
		}

		// 当たり判定の部分に青色を塗る
		for (int j = 0; j < mapData[2].size(); ++j)
		{
			for (int k = 0; k < mapData[2][j].size(); ++k)
			{
				if (mapData[2][j][k] != 0)
				{
					Rect(k * 32, j * 32, 32, 32).draw(ColorF(0, 0, 1.0, 0.5));
				}
			}
		}

		// デバッグ用
		font(x).draw(30, 0, ColorF(0, 0, 0));
		font(y).draw(30, 80, ColorF(0, 0, 0));

		// 左矢印
		if (KeyLeft.pressed())
		{
			// 移動しようとしている所が障害物じゃなければ
			if (mapData[2][int(y / 32)][int((x - 32) / 32)] == 0
				&& 0 < x - 32)
			{
				x -= delta;
			}
		}

		// 右矢印
		if (KeyRight.pressed())
		{
			// 移動しようとしている所が障害物じゃなければ
			if (mapData[2][int(y / 32)][int((x + 32) / 32)] == 0
				&& x + 32 < 512-20)
			{
				x += delta;
			}
		}

		// 上矢印
		if (KeyUp.pressed())
		{
			// 移動しようとしている所が障害物じゃなければ
			if (mapData[2][int((y - 32) / 32)][int(x / 32)] == 0
				&& 0 < y - 32)
			{
				y -= delta;
			}
		}

		// 下矢印
		if (KeyDown.pressed())
		{
			// 移動しようとしている所が障害物じゃなければ
			if (mapData[2][int((y + 32) / 32)][int(x / 32)] == 0
				&& y + 32 < 512-28)
			{
				y += delta;
			}
		}

		// ノーマル状態((x, y) = (20, 0) から横20、縦28)の
		// Siv3Dくんを2倍にして表示
		siv3d_kun(20, 0, 20, 28).scaled(2.0).draw(Arg::bottomCenter(x, y));
	}
}
