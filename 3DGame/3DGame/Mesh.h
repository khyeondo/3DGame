#pragma once
#include <fstream>
#include <strstream>
#include <vector>
#include <string>
#include "Polygon.h"
using namespace std;
struct Mesh
{
	vector<Polygon> polys;
	
	void operator *= (Matrix4X4& mat)
	{
		//int size = polys.size();
		//for (int i = 0; i < size; i++)
		//{
		//	Polygon& poly = polys[i];
		//	poly.vertex[0] *= mat;
		//	poly.vertex[1] *= mat;
		//	poly.vertex[2] *= mat;
		//}
		for (auto& poly : polys)
		{
			poly.vertex[0] *= mat;
			poly.vertex[1] *= mat;
			poly.vertex[2] *= mat;
		}
	}

	void Translate(Vec3 vec)
	{
		int size = polys.size();
		for (int i = 0; i < size; i++)
		{
			polys[i].Translate(vec);
		}
	}

	bool LoadFromObjectFile(string sFilename,bool bHasTexture = false)
	{
		ifstream f(sFilename);
		if (!f.is_open())
			return false;


		// Local cache of verts
		vector<Vec3> verts;
		vector<Vec2> texs;

		while (!f.eof())
		{
			char line[128];
			f.getline(line, 128);

			strstream s;
			s << line;

			char junk;

			if (line[0] == 'v')
			{
				if (line[1] == 't')
				{
					Vec3 v;
					s >> junk >> junk >> v.x >> v.y;
					// A little hack for the spyro texture
					//v.u = 1.0f - v.u;
					//v.v = 1.0f - v.v;
					verts.push_back(v);
				}
				else
				{
					Vec3 v;
					s >> junk >> v.x >> v.y >> v.z;
					verts.push_back(v);
				}
				//Vec3 v;
				//s >> junk >> v.x >> v.y >> v.z;
				//verts.push_back(v);
			}
			if (!bHasTexture)
			{
				if (line[0] == 'f')
				{
					int f[3];
					s >> junk >> f[0] >> f[1] >> f[2];
					polys.push_back({ verts[f[0] - 1], verts[f[1] - 1], verts[f[2] - 1] });
				}
			}
			else
			{
				if (line[0] == 'f')
				{
					s >> junk;

					string tokens[6];
					int nTokenCount = -1;


					while (!s.eof())
					{
						char c = s.get();
						if (c == ' ' || c == '/')
							nTokenCount++;
						else
							tokens[nTokenCount].append(1, c);
					}

					tokens[nTokenCount].pop_back();


					polys.push_back({ verts[stoi(tokens[0]) - 1], verts[stoi(tokens[2]) - 1], verts[stoi(tokens[4]) - 1],
						texs[stoi(tokens[1]) - 1], texs[stoi(tokens[3]) - 1], texs[stoi(tokens[5]) - 1] });

				}

			}
			//if (line[0] == 'f')
			//{
			//	int f[3];
			//	s >> junk >> f[0] >> f[1] >> f[2];
			//	polys.push_back({ verts[f[0] - 1], verts[f[1] - 1], verts[f[2] - 1] });
			//}
		}

		for (unsigned int i = 0; i < polys.size(); i += 2)
		{
			polys[i].uv[0] = Vec2(0, 1);
			polys[i].uv[1] = Vec2(0, 0);
			polys[i].uv[2] = Vec2(1, 1);

			polys[i + 1].uv[0] = Vec2(1, 1);
			polys[i + 1].uv[1] = Vec2(0, 0);
			polys[i + 1].uv[2] = Vec2(1, 0);
		}
		return true;
	}

	void SetCube(Vec3 center, Vec3 size)
	{
		Vec3 P[8];

		P[0].x = 0 - center.x;	    P[0].y = 0 - center.y;		P[0].z = 0 - center.z;
		P[1].x = size.x - center.x;	P[1].y = 0 - center.y;		P[1].z = 0 - center.z;
		P[2].x = 0 - center.x;		P[2].y = size.y - center.y;	P[2].z = 0 - center.z;
		P[3].x = size.x - center.x;	P[3].y = size.y - center.y;	P[3].z = 0 - center.z;
		P[4].x = 0 - center.x;		P[4].y = 0 - center.y;		P[4].z = size.z - center.z;
		P[5].x = size.x - center.x;	P[5].y = 0 - center.y;		P[5].z = size.z - center.z;
		P[6].x = 0 - center.x;		P[6].y = size.y - center.y;	P[6].z = size.z - center.z;
		P[7].x = size.x - center.x;	P[7].y = size.y - center.y;	P[7].z = size.z - center.z;

		Polygon arrPoly[12];

		arrPoly[0].vertex[0] = P[0];
		arrPoly[0].vertex[1] = P[2];
		arrPoly[0].vertex[2] = P[1];

		arrPoly[1].vertex[0] = P[1];
		arrPoly[1].vertex[1] = P[2];
		arrPoly[1].vertex[2] = P[3];

		arrPoly[2].vertex[0] = P[4];
		arrPoly[2].vertex[1] = P[5];
		arrPoly[2].vertex[2] = P[6];

		arrPoly[3].vertex[0] = P[5];
		arrPoly[3].vertex[1] = P[7];
		arrPoly[3].vertex[2] = P[6];

		arrPoly[4].vertex[0] = P[6];
		arrPoly[4].vertex[1] = P[7];
		arrPoly[4].vertex[2] = P[2];

		arrPoly[5].vertex[0] = P[7];
		arrPoly[5].vertex[1] = P[3];
		arrPoly[5].vertex[2] = P[2];

		arrPoly[6].vertex[0] = P[7];
		arrPoly[6].vertex[1] = P[5];
		arrPoly[6].vertex[2] = P[3];

		arrPoly[7].vertex[0] = P[5];
		arrPoly[7].vertex[1] = P[1];
		arrPoly[7].vertex[2] = P[3];

		arrPoly[8].vertex[0] = P[5];
		arrPoly[8].vertex[1] = P[4];
		arrPoly[8].vertex[2] = P[1];

		arrPoly[9].vertex[0] = P[4];
		arrPoly[9].vertex[1] = P[0];
		arrPoly[9].vertex[2] = P[1];

		arrPoly[10].vertex[0] = P[4];
		arrPoly[10].vertex[1] = P[6];
		arrPoly[10].vertex[2] = P[0];

		arrPoly[11].vertex[0] = P[6];
		arrPoly[11].vertex[1] = P[2];
		arrPoly[11].vertex[2] = P[0];

		for (int i = 0; i < 12; i++)
		{
			polys.push_back(arrPoly[i]);
		}
		for (int i = 0; i < 12; i += 2)
		{
			polys[i].uv[0] = Vec2(0, 1);
			polys[i].uv[1] = Vec2(0, 0);
			polys[i].uv[2] = Vec2(1, 1);

			polys[i + 1].uv[0] = Vec2(1, 1);
			polys[i + 1].uv[1] = Vec2(0, 0);
			polys[i + 1].uv[2] = Vec2(1, 0);
		}
	}
	void SetPlane(Vec3 center, Vec3 size)
	{
		Vec3 p[4];
		Vec2 uv[4];
		/*
		0       1

		2       3
		*/

		p[0].x = center.x - size.x / 2.f;
		p[0].z = center.z + size.z / 2.f;
		p[0].y = 0.f;
		uv[0] = { 0,1 };

		p[1].x = center.x + size.x / 2.f;
		p[1].z = center.z + size.z / 2.f;
		p[1].y = 0.f;
		uv[1] = { 1,1 };

		p[2].x = center.x - size.x / 2.f;
		p[2].z = center.z - size.z / 2.f;
		p[2].y = 0.f;
		uv[2] = { 0,0 };

		p[3].x = center.x + size.x / 2.f;
		p[3].z = center.z - size.z / 2.f;
		p[3].y = 0.f;
		uv[3] = { 1,0 };



		Polygon poly[2];
		poly[0].vertex[0] = p[1];
		poly[0].vertex[1] = p[2];
		poly[0].vertex[2] = p[0];
		poly[0].uv[0] = uv[1];
		poly[0].uv[1] = uv[2];
		poly[0].uv[2] = uv[0];

		poly[1].vertex[0] = p[3];
		poly[1].vertex[1] = p[2];
		poly[1].vertex[2] = p[1];
		poly[1].uv[0] = uv[3];
		poly[1].uv[1] = uv[2];
		poly[1].uv[2] = uv[1];

		for (int i = 0; i < 2; i++)
			polys.push_back(poly[i]);
	}
};