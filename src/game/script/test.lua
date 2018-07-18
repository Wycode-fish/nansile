test = {
    name = "eason",
    array = {1, 2, 3, 5},
    sum = function (x, y)
    return x + y;
    end
}


function Update(this)
    rotation = this.transform.rotation;
    new_rotation = vec3(rotation.x + 0.005, rotation.y + 0.005, rotation.z);
    this.transform.rotation = new_rotation;
end;
