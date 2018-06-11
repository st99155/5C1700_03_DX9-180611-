#include "stdafx.h"
#include "ObjLoader.h"
//#include "GlobalDefinition.h"

const int TOKEN_SIZE = 128;


ObjLoader::ObjLoader()
{
}

ObjLoader::~ObjLoader()
{
}

LPD3DXMESH ObjLoader::LoadMesh(LPCTSTR filepath, LPCTSTR filename, D3DXMATRIXA16 * pMat, vector<MTLTEX*>& vecMtltex)
{
	vector<D3DXVECTOR3> vecP;
	vector<D3DXVECTOR2> vecT;
	vector<D3DXVECTOR3> vecN;
	vector<VERTEX_PNT> vecPNT;
	vector<DWORD> vecAttbuf;
	CString mtlName;
	char token[TOKEN_SIZE];

	m_filepath = filepath;

	std::ifstream fin;
	fin.open(m_filepath + filename);

	if (fin.is_open() == false)
		assert(false && "fin.is_open()== false");

	while (fin.eof() == false)
	{
		fin >> token;
		if (CompareStr(token, "mtllib"))
		{
			fin >> token;
			LoadMtlLib(m_filepath + token);

			vecMtltex.resize(m_mtltexList.size());
			for (auto p : m_mtltexList)
			{
				vecMtltex[p.second->id] = p.second;
			}
		}
		else if (CompareStr(token, "v"))
		{
			float x, y, z;
			fin.getline(token, TOKEN_SIZE);
			sscanf_s(token, "%f %f %f", &x, &y, &z);
			vecP.push_back(D3DXVECTOR3(x, y, z));
		}
		else if (CompareStr(token, "vt"))
		{
			float x, y;
			fin.getline(token, TOKEN_SIZE);
			sscanf_s(token, "%f %f", &x, &y);
			vecT.push_back(D3DXVECTOR2(x, y));
		}
		else if (CompareStr(token, "vn"))
		{
			float x, y, z;
			fin.getline(token, TOKEN_SIZE);
			sscanf_s(token, "%f %f %f", &x, &y, &z);
			vecN.push_back(D3DXVECTOR3(x, y, z));
		}
		else if (CompareStr(token, "usemtl"))
		{
			fin >> token;
			mtlName = token;			//현재 사용할 mtl name
		}
		else if (CompareStr(token, "f"))
		{
			int aIndex[3][3];
			fin.getline(token, TOKEN_SIZE);
			sscanf_s(token, "%d/%d/%d %d/%d/%d %d/%d/%d",
				&aIndex[0][0], &aIndex[0][1], &aIndex[0][2],
				&aIndex[1][0], &aIndex[1][1], &aIndex[1][2],
				&aIndex[2][0], &aIndex[2][1], &aIndex[2][2]);

			for (int i = 0; i < 3; i++)
			{
				VERTEX_PNT pnt;
				pnt.p = vecP[aIndex[i][0] - 1];
				pnt.t = vecT[aIndex[i][1] - 1];
				pnt.n = vecN[aIndex[i][2] - 1];

				if (pMat)
				{
					D3DXVec3TransformCoord(&pnt.p, &pnt.p, pMat);
					D3DXVec3TransformNormal(&pnt.p, &pnt.n, pMat);
				}
				vecPNT.push_back(pnt);
			}

			//면마다 하나씩 가짐. 면이 어떤 mtltex를 쓸건지 정보 가지고있음.
			vecAttbuf.push_back(m_mtltexList[mtlName]->id);
		
		}
	}

	m_mtltexList.clear();
	fin.close();
	//vertex정보 다 받아옴
	LPD3DXMESH pMesh = NULL;
	D3DXCreateMeshFVF(vecPNT.size() / 3, vecPNT.size(),
		D3DXMESH_MANAGED | D3DXMESH_32BIT , VERTEX_PNT::FVF, DX::GetDevice(), &pMesh);
		//d3dxmesh_managed : device에서 알아서 메모리 관리
		//d3dxmesh_32bit : 지정 안해주면 16bit사용

	VERTEX_PNT* pV = NULL;
	DWORD flags = 0;
	pMesh->LockVertexBuffer(flags, (LPVOID*)&pV);
	memcpy(pV, &vecPNT[0], vecPNT.size() * sizeof(VERTEX_PNT));
	pMesh->UnlockVertexBuffer();

	DWORD* pI = NULL; // index
	pMesh->LockIndexBuffer(flags, (LPVOID*)&pI);
	for (size_t i = 0; i < vecPNT.size(); i++)
	{
		pI[i] = i;

	}
	pMesh->UnlockIndexBuffer();


	DWORD* pA = NULL;
	pMesh->LockAttributeBuffer(flags, &pA);
	memcpy(pA, &vecAttbuf[0], vecAttbuf.size() * sizeof(DWORD));
	pMesh->UnlockAttributeBuffer();


	vector<DWORD> vecAdjacency(pMesh->GetNumFaces() * 3);
	pMesh->GenerateAdjacency(FLT_EPSILON, &vecAdjacency[0]);		//이 수치 이하의 삼각형은 인접한걸로 간주
	pMesh->OptimizeInplace(D3DXMESHOPT_COMPACT | D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_VERTEXCACHE, &vecAdjacency[0], NULL, NULL, NULL);
	

	return pMesh;
}

void ObjLoader::LoadMtlLib(LPCTSTR fullpath)
{
	CString mtlName;
	DWORD mtltexID = 0;
	char token[TOKEN_SIZE];
	std::ifstream fin;

	fin.open(fullpath);

	if (fin.is_open() == false)
		assert(false && "fin.is_open() == false");

	while (fin.eof() == false)
	{
		fin >> token;

		if (CompareStr(token, "newmtl"))
		{
			fin >> token;
			mtlName = token;
			if (m_mtltexList.find(mtlName) == m_mtltexList.end())
			{
				m_mtltexList[mtlName] = new MTLTEX;
				m_mtltexList[mtlName]->id = mtltexID;
				mtltexID++;
			}
			
		}
		else if (CompareStr(token, "Ka"))
		{
			D3DCOLORVALUE c;
			fin.getline(token, TOKEN_SIZE);
			sscanf_s(token, "%f %f %f", &c.r, &c.g, &c.b);
			c.a = 1.0f;
			m_mtltexList[mtlName]->material.Ambient = c;
		}

		else if (CompareStr(token, "Kd"))
		{
			D3DCOLORVALUE c;
			fin.getline(token, TOKEN_SIZE);
			sscanf_s(token, "%f %f %f", &c.r, &c.g, &c.b);
			c.a = 1.0f;
			m_mtltexList[mtlName]->material.Diffuse = c;
		}
		else if (CompareStr(token, "Ks"))
		{
			D3DCOLORVALUE c;
			fin.getline(token, TOKEN_SIZE);
			sscanf_s(token, "%f %f %f", &c.r, &c.g, &c.b);
			c.a = 1.0f;
			m_mtltexList[mtlName]->material.Specular = c;
		}
		else if (CompareStr(token, "map_Kd"))
		{
			fin >> token;
			m_mtltexList[mtlName]->pTexture = g_pTextureManager->GetTexture(m_filepath + token);
		}

	}
}
