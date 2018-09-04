MeshRenderer = 
{
	Material = 
	{
		Shader =
	    {
	        vertex_shader_path = "src/gl/shaders/basic/skybox.vertex",
	        fragment_shader_path = "src/gl/shaders/basic/skybox.fragment"
	    },

	    Attributes = 
	    { status = "Inactive" }
	},

	Model = 
	{
		Meshes = 
		{

			mesh1 = {

				texture = 
			    {
			    	texture_type = "CubeMap",
			        texture_paths =
			        {
			        	"res/images/skybox/Nalovardo/posx.jpg",
			            "res/images/skybox/Nalovardo/negx.jpg",
			            "res/images/skybox/Nalovardo/posy.jpg",
			            "res/images/skybox/Nalovardo/negy.jpg",
			            "res/images/skybox/Nalovardo/posz.jpg",
			            "res/images/skybox/Nalovardo/negz.jpg"
			        },
			    },

			    model =
			    {
			        surface_count = 6,
			        vertex_count_per_surface = 4,
			        attr_float_per_vertex = 3,
			        idx_per_surface = 6,
			        layout_elements = { 3 },
			        vertex_position =
			        {
			            -1.0, -1.0, 1.0,
			            1.0, -1.0, 1.0,
			            1.0, 1.0, 1.0,
			            -1.0, 1.0, 1.0,
			            
			            1.0, 1.0, 1.0,
			            1.0, 1.0, -1.0,
			            1.0, -1.0, -1.0,
			            1.0, -1.0, 1.0,
			            
			            -1.0, -1.0, -1.0,
			            1.0, -1.0, -1.0,
			            1.0, 1.0, -1.0,
			            -1.0, 1.0, -1.0,
			            
			            -1.0, -1.0, -1.0,
			            -1.0, -1.0, 1.0,
			            -1.0, 1.0, 1.0,
			            -1.0, 1.0, -1.0,
			            
			            1.0, 1.0, 1.0,
			            1.0, 1.0, -1.0,
			            -1.0, 1.0, -1.0,
			            -1.0, 1.0, 1.0,
			            
			            -1.0, -1.0, -1.0,
			            1.0, -1.0, -1.0,
			            1.0, -1.0, 1.0,
			            -1.0, -1.0, 1.0,
			        },

			        vertex_indicies =
			        {
			            4, 5, 6, 4, 6, 7,
			            12, 13, 14, 12, 14, 15,
			            16, 17, 18, 16, 18, 19,
			            20, 21, 22, 20, 22, 23,
			            8, 9, 10, 8, 10, 11,   
			            0, 1, 2, 2, 3, 0
			        }
			    }
			}  
		}
	}
}
