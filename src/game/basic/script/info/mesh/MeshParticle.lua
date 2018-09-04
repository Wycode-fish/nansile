MeshRenderer = 
{
	Material = 
	{
		Shader =
	    {
	        vertex_shader_path = "src/gl/shaders/basic/particle.vertex",
	        fragment_shader_path = "src/gl/shaders/basic/particle.fragment"
	    },

	    Attributes = 
	    {
            status  = "Active",
	    	ambient = vec3(1.0, 1.0, 1.0),
	    	diffuse = vec3(0.0, 0.0, 0.0),
	    	specular = vec3(0.0, 0.0, 0.0),
	    	shiness = 0.0,
	    	transparency = 1.0
		}
	},

	Model = 
	{
		Meshes = 
		{

			mesh1 = {

				texture = 
			    {
			    	texture_type = "Default",
			        texture_paths =
			        { "res/images/light.png"},
			    },

			    model =
			    {
			        surface_count = 1,
			        vertex_count_per_surface = 4,
			        attr_float_per_vertex = 5,
			        idx_per_surface = 6,
			        layout_elements = { 3, 2 },
			        vertex_position =
			        {
			        	-1.0, -1.0, 0.0, 0.0, 0.0,
			        	-1.0, 1.0, 0.0, 1.0, 0.0,
			        	1.0, 1.0, 0.0, 1.0, 1.0,
			        	1.0, -1.0, 0.0, 0.0, 1.0
			        },

			        vertex_indicies =
			        {
			            0, 1, 2, 
			            2, 3, 0
			        }
			    }
			}  
		}
	}
}
