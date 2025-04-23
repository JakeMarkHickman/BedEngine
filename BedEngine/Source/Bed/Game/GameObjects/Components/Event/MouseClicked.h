#prgama once

namespace Bed
{
    struct MouseClicked
    {
        MouseClicked(uint64_t clickedEntity) : ClickedEntity(clickedEntity) {};

        uint64_t ClickedEntity;

        //TODO: store where clicked
        //TODO: store what button was clicked e.g RMB LBM MMB
    };
    
}