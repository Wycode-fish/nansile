test = {
    name = "eason",
    id = 2,
    array = {1, 2, 3, 5},
    sum = function (x, y)
    return x + y;
    end
}

SpinningCube = {

    rotationVel = vec3(0.005, 0.005, 0.0),

    Update = function (this)
        rotation = this.transform.rotation;
        new_rotation = vec3(rotation.x + SpinningCube.rotationVel.x,
                            rotation.y + SpinningCube.rotationVel.y,
                            rotation.z + SpinningCube.rotationVel.z);
        this.transform.rotation = new_rotation;
    end
}

--function Update(this)
    --rotation = this.transform.rotation;
    --new_rotation = vec3(rotation.x, rotation.y + 0.005, rotation.z);
    --this.transform.rotation = new_rotation;
    --ambient_color = this.meshRenderer.material.matAttribs.ambient;
    --print (ambient_color.x.." "..ambient_color.y.." "..ambient_color.z);
--end;
