#ifndef APE_CAMERA_H
#define APE_CAMERA_H

#include <ape/core/component.h>
#include <ape/core/rect.h>

namespace ape {
   /* Camera system overview:
      A camera/view system can be used to allow only a specific part of 
      the world to be rendered. The camera can then be manipulated to 
      allow different views. In the engine, the camera is very closely 
      linked to the scene graph system.

      - A camera component can be attached to an entity. This 
        encodes zoom information/the area of the world being 
        looked at and calculates information for rendering. 
        It also links the camera to a viewport. This has the 
        advantage that the entity's transform component can 
        be used to control the camera's position and even 
        velocity.
      - In the scene-graph, a node has a setCamera function which 
        means it will be rendered under that camera and the 
        corresponding viewport. The camera setting cascades down 
        to all child nodes. A camera cannot be linked to a child 
        node if the parent has a camera linked. This will mean that 
        only top level nodes (nodes which are direct children of the 
        root node) can have a camera attached. As a result, the 
        setCamera function should fail if the node is not a child 
        of the root node.
      - Further to this, if a node is removed ("orphaned") then the 
        camera setting should be cleared until it is reattached. 
        Conversely, upon reattachement, the node should inherit the 
        camera setting of its parent.
      - The setCamera function should take as a parameter an action 
        to execute if the camera entity is deleted. These actions 
        could include DELETE_ALL_CHILDREN (e.g. useful for 
        temporary nodes such as cut-scenes; this would delete all 
        relevant entities) and REATTACH (which would allow entities
        to be reattached to a different camera).
      - Cameras have viewports attached (encoded in the component) 
        which correspond to viewports in SDL. If there is no viewport, 
        then it should resolve to a default viewport (i.e. the entire window)
      - The camera component also contains the area it looks at. A naive 
        culling method could be used, in which all transform components 
        are iterated over and those outside the area are marked as excluded.
   */

   struct Camera : public Component<Camera> {
       Camera(entity_t entity) : Component<Camera>(entity) {}  

       FloatRect viewport;
       float zoom;
   };

   namespace scene {
       extern entity_t DEFAULT_CAMERA;
   }
  
    
}

#endif