# A Pixel Life

I plan on adding more features to this project, namely collision detection, mining capabilities, and hostile mobs. Collision detection would require me to do some research. I'm not sure if a simple hitbox sensing block collisions around the perimeter of the player is the best strategy or not. If I went with this idea, I'd face some difficulty with map's data structure. It's a 1D vertex array storing block objects, so I'd have to keep track of which index segments the player is within, and check whether their boundaries are permissible.

![Preview](resource/prototype_preview.PNG)
