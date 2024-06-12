#pragma once

#include "Common.h"

#include "Renderer/DataTypes.h"
#include "Renderer/Renderable.h"
#include "Shader/PixelShader.h"
#include "Shader/VertexShader.h"
#include "Texture/Material.h"

struct aiScene;
struct aiMesh;
struct aiMaterial;
struct aiAnimation;
struct aiBone;
struct aiNode;
struct aiNodeAnim;

namespace Assimp
{
    class Importer;
}

class Model : public Renderable
{
public:
    Model() = default;
    Model(_In_ const std::filesystem::path& filePath);
    virtual ~Model() = default;

    virtual HRESULT Initialize(_In_ ID3D11Device* pDevice, _In_ ID3D11DeviceContext* pImmediateContext);
    virtual void Update(_In_ FLOAT deltaTime) override;

    virtual UINT GetNumVertices() const override;
    virtual UINT GetNumIndices() const override;

protected:
    void countVerticesAndIndices(_Inout_ UINT& uOutNumVertices, _Inout_ UINT& uOutNumIndices, _In_ const aiScene* pScene);
    const virtual SimpleVertex* getVertices() const override;
    virtual const WORD* getIndices() const override;
    void initAllMeshes(_In_ const aiScene* pScene);
    HRESULT initFromScene(
        _In_ ID3D11Device* pDevice,
        _In_ ID3D11DeviceContext* pImmediateContext,
        _In_ const aiScene* pScene,
        _In_ const std::filesystem::path& filePath
    );
    HRESULT initMaterials(
        _In_ ID3D11Device* pDevice,
        _In_ ID3D11DeviceContext* pImmediateContext,
        _In_ const aiScene* pScene,
        _In_ const std::filesystem::path& filePath
    );
    void initSingleMesh(_In_ const aiMesh* pMesh);
    void loadColors(_In_ const aiMaterial* pMaterial, _In_ UINT uIndex);
    HRESULT loadDiffuseTexture(
        _In_ ID3D11Device* pDevice,
        _In_ ID3D11DeviceContext* pImmediateContext,
        _In_ const std::filesystem::path& parentDirectory,
        _In_ const aiMaterial* pMaterial,
        _In_ UINT uIndex
    );
    HRESULT loadSpecularTexture(
        _In_ ID3D11Device* pDevice,
        _In_ ID3D11DeviceContext* pImmediateContext,
        _In_ const std::filesystem::path& parentDirectory,
        _In_ const aiMaterial* pMaterial,
        _In_ UINT uIndex
    );
    HRESULT loadTextures(
        _In_ ID3D11Device* pDevice,
        _In_ ID3D11DeviceContext* pImmediateContext,
        _In_ const std::filesystem::path& parentDirectory,
        _In_ const aiMaterial* pMaterial,
        _In_ UINT uIndex
    );
    void reserveSpace(_In_ UINT uNumVertices, _In_ UINT uNumIndices);

protected:
    static std::unique_ptr<Assimp::Importer> sm_pImporter;

    std::filesystem::path m_filePath;

    ComPtr<ID3D11Buffer> m_animationBuffer;
    ComPtr<ID3D11Buffer> m_skinningConstantBuffer;

    std::vector<SimpleVertex> m_aVertices;

    std::vector<WORD> m_aIndices;
    std::vector<XMMATRIX> m_aTransforms;
    std::unordered_map<std::string, UINT> m_boneNameToIndexMap;

    const aiScene* m_pScene;

    float m_timeSinceLoaded;

    XMMATRIX m_globalInverseTransform;
};