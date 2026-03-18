#pragma once
namespace nam
{
	class BoxObserver
	{
		DirectX::XMFLOAT3 m_extends;
		DirectX::XMFLOAT3 m_positionOffset;
		bool m_isSphere = false;
		bool m_isBox = true;
	};
}
