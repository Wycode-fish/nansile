MeshRenderer = 
{
	Material = 
	{
		Shader =
	    {
	        vertex_shader_path = "src/gl/shaders/basic/grid.vertex",
	        fragment_shader_path = "src/gl/shaders/basic/grid.fragment"
	    },

	    Attributes = 
	    {
            status  = "Active",
	    	ambient = vec3(1.0, 1.0, 1.0),
	    	diffuse = vec3(0.5, 0.5, 0.5),
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
			        {},
			    },

			    model =
			    {
			        surface_count = 1,
			        vertex_count_per_surface = 4,
			        attr_float_per_vertex = 3,
			        idx_per_surface = 6,
			        layout_elements = { 3 },
			        vertex_position =
			        {
			        	-1.0, 0.0, -1.0,
			        	-1.0, 0.0, 1.0,
			        	1.0, 0.0, 1.0,
			        	1.0, 0.0, -1.0
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
