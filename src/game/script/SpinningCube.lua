SpinningCube = {

    rotationVel = vec3(0.005, 0.005, 0.0),

    id = 2,
    
	public = 
	{
		rotationVel = vec3(0.005, 0.005, 0.0),

	    Update = function (this)
	        rotation = this.transform.rotation;
	        new_rotation = vec3(rotation.x + SpinningCube.public.rotationVel.x,
	                            rotation.y + SpinningCube.public.rotationVel.y,
	                            rotation.z + SpinningCube.public.rotationVel.z);
	        this.transform.rotation = new_rotation;
	    end
	},
    
}
