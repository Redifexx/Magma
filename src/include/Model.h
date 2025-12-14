#pragma once

#include <Mesh.h>
#include <string>
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Magma
{
	class Model
	{
		public:
			Model(const std::string& filepath);
			void Draw() const;

		private:
			std::vector<Mesh> m_Meshes;
			std::string m_Directory;

			void ProcessNode(aiNode* node, const aiScene* scene);
			void ProcessMesh(aiMesh* mesh, const aiScene* scene);
	};
}