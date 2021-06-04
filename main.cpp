#include <tuple>
#include <utility>
#include <cstddef>

namespace coco2d
{
    class CCZone;
    class CCObject;
    class CCCamera;
    class CCGridBase;
    class CCDataVisitor;
    class CCActionManager;
    class CCScheduler;
    class CCGLProgram;
    class CCComponent;
    class CCComponentContainer;

    class __declspec(novtable, align(4)) CCCopying
    {
    public:
        virtual auto copyWithZone(CCZone* pZone) -> CCObject* = 0;
    };

    class __declspec(novtable, align(4)) CCObject : public CCCopying
    {
    public:
        unsigned int        m_uID;
        int                 m_nLuaID;
    protected:
        unsigned int        m_uReference;
        unsigned int        m_uAutoReleaseCount;
    public:
        virtual ~CCObject(void) = 0;
        virtual auto isEqual(const CCObject* pObject) -> bool = 0;
        virtual auto acceptVisitor(CCDataVisitor& visitor) -> void = 0;
        virtual auto update(float dt) -> void = 0;
    };

    struct __declspec(novtable, align(4)) CCArray : CCObject
    {
        struct alignas(4)
        {
            std::size_t size, capacity;
            CCObject** data;
        } *inner;
    };

    using CCSize = std::pair<float, float>;
    using CCPoint = std::pair<float, float>;

    using CCRect = std::pair<CCPoint, CCSize>;
    using CCAffineTransform = std::tuple<float, float, float, float, float, float>;

    enum ccScriptType : int
    {
        kScriptTypeNone = 0,
        kScriptTypeLua,
        kScriptTypeJavascript
    };

    enum ccGLServerState : int
    {
        CC_GL_ALL = 0
    };

    class __declspec(novtable, align(4)) CCNode : public CCObject
    {
    public:
        virtual ~CCNode() = 0;
        virtual auto init() -> void = 0;
        virtual auto setZOrder(int zOrder) -> void = 0;
        virtual auto _setZOrder(int z) -> void = 0;
        virtual auto getZOrder() -> int = 0;
        virtual auto setVertexZ(float vertexZ) -> void = 0;
        virtual auto getVertexZ() -> float = 0;
        virtual auto setScaleX(float fScaleX) -> void = 0;
        virtual auto getScaleX() -> float = 0;
        virtual auto setScaleY(float fScaleY) -> void = 0;
        virtual auto getScaleY() -> float = 0;
        virtual auto setScale(float scale) -> void = 0;
        virtual auto getScale() -> float = 0;
        virtual auto setScale(float fScaleX, float fScaleY) -> void = 0;
        virtual auto setPosition(const CCPoint& position) -> void = 0;
        virtual auto getPosition() -> const CCPoint & = 0;
        virtual auto setPosition(float x, float y) -> void = 0;
        virtual auto getPosition(float* x, float* y) -> void = 0;
        virtual auto setPositionX(float x) -> void = 0;
        virtual auto getPositionX(void) -> float = 0;
        virtual auto setPositionY(float y) -> void = 0;
        virtual auto getPositionY(void) -> float = 0;
        virtual auto setSkewX(float fSkewX) -> void = 0;
        virtual auto getSkewX() -> float = 0;
        virtual auto setSkewY(float fSkewY) -> void = 0;
        virtual auto getSkewY() -> float = 0;
        virtual auto setAnchorPoint(const CCPoint& anchorPoint) -> void = 0;
        virtual auto getAnchorPoint() -> const CCPoint& = 0;
        virtual auto getAnchorPointInPoints() -> const CCPoint& = 0;
        virtual auto setContentSize(const CCSize& contentSize) -> void = 0;
        virtual auto getContentSize() const -> const CCSize& = 0;
        virtual auto setVisible(bool visible) -> void = 0;
        virtual auto isVisible() -> bool = 0;
        virtual auto setRotation(float fRotation) -> void = 0;
        virtual auto getRotation() -> float = 0;
        virtual auto setRotationX(float fRotaionX) -> void = 0;
        virtual auto getRotationX() -> float = 0;
        virtual auto setRotationY(float fRotationY) -> void = 0;
        virtual auto getRotationY() -> float = 0;
        virtual auto setOrderOfArrival(unsigned int uOrderOfArrival) -> void = 0;
        virtual auto getOrderOfArrival() -> unsigned int = 0;
        virtual auto setGLServerState(ccGLServerState glServerState) -> void = 0;
        virtual auto getGLServerState()->ccGLServerState = 0;
        virtual auto ignoreAnchorPointForPosition(bool ignore) -> void = 0;
        virtual auto isIgnoreAnchorPointForPosition() -> bool = 0;
        virtual auto addChild(CCNode* child) -> void = 0;
        virtual auto addChild(CCNode* child, int zOrder) -> void = 0;
        virtual auto addChild(CCNode* child, int zOrder, int tag) -> void = 0;
        virtual auto getChildByTag(int tag)->CCNode* = 0;
        virtual auto getChildren()->CCArray* = 0;
        virtual auto getChildrenCount(void) const -> unsigned int = 0;
        virtual auto setParent(CCNode* parent) -> void = 0;
        virtual auto getParent()-> CCNode* = 0;
        virtual auto removeFromParent() -> void = 0;
        virtual auto removeFromParentAndCleanup(bool cleanup) -> void = 0;
        virtual auto removeChild(CCNode* child) -> void = 0;
        virtual auto removeChild(CCNode* child, bool cleanup) -> void = 0;
        virtual auto removeChildByTag(int tag) -> void = 0;
        virtual auto removeChildByTag(int tag, bool cleanup) -> void = 0;
        virtual auto removeAllChildren() -> void = 0;
        virtual auto removeAllChildrenWithCleanup(bool cleanup) -> void = 0;
        virtual auto reorderChild(CCNode* child, int zOrder) -> void = 0;
        virtual auto sortAllChildren() -> void = 0;
        virtual auto getGrid()->CCGridBase* = 0;
        virtual auto setGrid(CCGridBase* pGrid) -> void = 0;
        virtual auto getTag() const -> int = 0;
        virtual auto setTag(int nTag) -> void = 0;
        virtual auto getUserData() -> void* = 0;
        virtual auto setUserData(void* pUserData) -> void = 0;
        virtual auto getUserObject()->CCObject* = 0;
        virtual auto setUserObject(CCObject* pUserObject) -> void = 0;
        virtual auto getShaderProgram()->CCGLProgram* = 0;
        virtual auto setShaderProgram(CCGLProgram* pShaderProgram) -> void = 0;
        virtual auto getCamera()->CCCamera* = 0;
        virtual auto isRunning() -> bool = 0;
        virtual auto registerScriptHandler(int handler) -> void = 0;
        virtual auto unregisterScriptHandler(void) -> void = 0;
        virtual auto onEnter() -> void = 0;
        virtual auto onEnterTransitionDidFinish() -> void = 0;
        virtual auto onExit() -> void = 0;
        virtual auto onExitTransitionDidStart() -> void = 0;
        virtual auto cleanup(void) -> void = 0;
        virtual auto draw(void) -> void = 0;
        virtual auto visit(void) -> void = 0;
        virtual auto boundingBox(void)->CCRect = 0;
        virtual auto setActionManager(CCActionManager* actionManager) -> void = 0;
        virtual auto getActionManager()->CCActionManager* = 0;
        virtual auto setScheduler(CCScheduler* scheduler) -> void = 0;
        virtual auto getScheduler()-> CCScheduler* = 0;
        virtual auto update(float delta) -> void = 0;
        virtual auto updateTransform(void) -> void = 0;
        virtual auto nodeToParentTransform(void) -> const CCAffineTransform & = 0;
        virtual auto parentToNodeTransform(void) -> const CCAffineTransform & = 0;
        virtual auto nodeToWorldTransform(void) -> CCAffineTransform = 0;
        virtual auto worldToNodeTransform(void) -> CCAffineTransform = 0;
        virtual auto addComponent(CCComponent* pComponent) -> bool = 0;
        virtual auto removeComponent(const char* pName) -> bool = 0;
        virtual auto removeComponent(CCComponent* pComponent) -> bool = 0;
        virtual auto removeAllComponents() -> void = 0;

    public:
        float m_fRotationX;                 
        float m_fRotationY;                 
        float m_fScaleX;                    
        float m_fScaleY;                    
        float m_fVertexZ;                   
        CCPoint m_obPosition;               
        float m_fSkewX;                     
        float m_fSkewY;                     
        CCPoint m_obAnchorPointInPoints;    
        CCPoint m_obAnchorPoint;            
        CCSize m_obContentSize;
        CCAffineTransform m_sAdditionalTransform;
        CCAffineTransform m_sTransform;     
        CCAffineTransform m_sInverse;       
        CCCamera* m_pCamera;                
        CCGridBase* m_pGrid;                
        int m_nZOrder;                      
        CCArray* m_pChildren;               
        CCNode* m_pParent;                  
        int m_nTag;                         
        void* m_pUserData;                  
        CCObject* m_pUserObject;            
        CCGLProgram* m_pShaderProgram;      
        ccGLServerState m_eGLServerState;   
        unsigned int m_uOrderOfArrival;     
        CCScheduler* m_pScheduler;          
        CCActionManager* m_pActionManager;  
        bool m_bRunning;                    
        bool m_bTransformDirty;             
        bool m_bInverseDirty;               
        bool m_bAdditionalTransformDirty;   
        bool m_bVisible;                  
        bool m_bIgnoreAnchorPointForPosition; 
        bool m_bReorderChildDirty;          
        int m_nScriptHandler;       
        int m_nUpdateScriptHandler;         
        ccScriptType m_eScriptType;         
        CCComponentContainer* m_pComponentContainer;
    };
}

#include <thread>
#include <type_traits>

#include <windows.h>

namespace memory
{
    template<typename T>
    [[nodiscard]] auto read(const std::uintptr_t addr) noexcept -> std::add_lvalue_reference_t<T>
    {
        return *reinterpret_cast<std::add_pointer_t<T>>(addr);
    }

    template<typename T, typename T1, typename ...Params>
    [[nodiscard]] auto read(std::uintptr_t addr, const T1 offset, const Params ... offsets) noexcept -> std::add_lvalue_reference_t<T>
    {
        addr = read<std::uintptr_t>(addr) + static_cast<std::uintptr_t>(offset);
        return read<T>(addr, offsets...);
    }
}

namespace evil
{
    static auto module = reinterpret_cast<std::uintptr_t>(GetModuleHandleW(nullptr));

    namespace offsets
    {
        constexpr std::uintptr_t attributes = 0x1a5b88;
        constexpr std::uintptr_t input = 0x1a5230;
    }
}

namespace evil
{
    class __declspec(novtable, align(4)) PTPInputController : public coco2d::CCObject
    {
        const void* const unused;
    public:
        coco2d::CCArray* const objects;
    };

    class __declspec(novtable, align(4)) PTPObjectAssetCharacter : public coco2d::CCNode
    {
    public:
        const void* const asset;
        const void* const asset_container;
        
        enum class State : int
        {
            JUMPING = 3,
            DEAD,
            DESTROYED,
        };

        State state;
    public:
        [[nodiscard]] static auto character() noexcept -> PTPObjectAssetCharacter*
        {
            if (const auto input = memory::read<const PTPInputController*>(evil::module + offsets::input))
            {
                const auto objects = reinterpret_cast<PTPObjectAssetCharacter**>(input->objects->inner->data);
                return input->objects->inner->size ? *objects : nullptr;
            }
            return nullptr;
        }
    };
}

auto run() noexcept -> void
{
    using namespace std::chrono_literals;

    while (true)
    {
        if (const auto character = evil::PTPObjectAssetCharacter::character())
        {
            auto& max_concurrent_jumps = memory::read<float>(reinterpret_cast<std::uintptr_t>(character) + 0x118, 0x24);
            max_concurrent_jumps = 4.0f;
        }

        std::this_thread::sleep_for(50ms);
    }
}

auto CALLBACK DllMain(HMODULE module, DWORD reason, [[maybe_unused]] LPVOID _) noexcept -> BOOL
{
    DisableThreadLibraryCalls(module);

    if (reason == DLL_PROCESS_ATTACH)
        std::thread(run).detach();

    return true;
}
