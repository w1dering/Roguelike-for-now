class Particle
{
public:
    int particle_x;
    int particle_y;
    int particle_size;

    Particle(int part_x, int part_y, int part_s) 
    {
        particle_x = part_x;
        particle_y = part_y;
        particle_size = part_s;
    }
};