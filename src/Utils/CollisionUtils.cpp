//
// Created by seekerses on 06.06.2024.
//

#include "CollisionUtils.h"
#include "SimpleMath.h"

DirectX::XMFLOAT4 Intersect(const DirectX::XMFLOAT4& ra, const DirectX::XMFLOAT4& rb) noexcept
{

	if (ra.x < rb.x + rb.z &&
		ra.x + ra.z > rb.x &&
		ra.y < rb.y + rb.w &&
		ra.y + ra.w > rb.y
		) {
		return DirectX::XMFLOAT4{ 1, 1, 1, 1 };
	} else {
		return DirectX::XMFLOAT4{ 0, 0, 0, 0 };
	}
//	float rbx2 = rb.x + rb.z;
//	float rax2 = ra.x + ra.z;
//	float ray2 = ra.y - ra.w;
//	float rby2 = rb.y - rb.w;
//	if (ra.x < rbx2 && rax2 > rb.x && ra.y > rby2 && ray2 < rb.y)
//	{
//		if (rb.y > ra.y && rby2 < ray2)
//		{
//			return DirectX::XMFLOAT4{ 1, 1, 1, 1 };
//		}
//		else
//		{
//			return DirectX::XMFLOAT4{ 2, 2, 2, 2 };
//		}
//	}
//	else
//	{
//		return DirectX::XMFLOAT4{ 0, 0, 0, 0 };
//	}
}
