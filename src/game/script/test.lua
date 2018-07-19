test = {
    name = "eason",
    id = 1,
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
