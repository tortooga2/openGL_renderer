//
// Created by Chase Nagle on 11/29/24.
//

#ifndef OPENGLPROJECT_GLOBALS_HPP
#define OPENGLPROJECT_GLOBALS_HPP






//Dont worry, however you can edit if you want to add new attributes
struct Vertex{
    float position[3];
    float normal[3];
    float color[3];
};

struct Vector3{
    float x;
    float y;
    float z;

    void Cross(Vector3 o){
        x = ( (y * o.z) - (z * o.y) );
        y = -((x*o.z)-(o.x * z));
        z = ((x * o.y) - (y * o.x));
    }

    void operator+=(const Vector3 &o){
        x += o.x;
        y += o.y;
        z += o.z;
    }

    void operator-=(const Vector3 &o){
        x -= o.x;
        y -= o.y;
        z -= o.z;
    }

};


static vector<float> getVerteciesFromMesh(vector<Vertex> mesh){
    std::vector<float> vertices;
    for (int i = 0; i < mesh.size(); i++) {
        vertices.push_back(mesh[i].position[0]);
        vertices.push_back(mesh[i].position[1]);
        vertices.push_back(mesh[i].position[2]);
    };

    return vertices;
}

static vector<float> getNormalsFromMesh(vector<Vertex> mesh){
    std::vector<float> vertices;
    for (int i = 0; i < mesh.size(); i++) {
        vertices.push_back(mesh[i].normal[0]);
        vertices.push_back(mesh[i].normal[1]);
        vertices.push_back(mesh[i].normal[2]);
    };

    return vertices;
}


static vector<vector<string>> convertFileToVector(string filename){
    fstream file (filename);

    if(!file.is_open()){
        throw std::runtime_error("Unable to Open File");
    }

    string f;
    vector<vector<string>> digestedFile;

    while(getline(file, f)){
        vector<string> tempVector;
        string temp;
        for(int i = 0; i < f.length(); i++){
            if(f[i] != ' '){
                temp += f[i];
            }
            else{

                tempVector.push_back(temp);
                temp = "";
            }
        }
        tempVector.push_back(temp);
        digestedFile.push_back(tempVector);
    };

    return digestedFile;

}

static std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);

    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}


static vector<Vertex> unpackOBJ(string filename){

    string fullPath = getFilePath(filename);
    vector<vector<string>> obj = convertFileToVector(fullPath);



    vector<Vector3> vertices;
    vector<Vector3> normal;

    vector<Vertex> mesh;

    for(int i = 0; i < obj.size(); i++) {
        if (obj[i][0] == "v") {
            float v1 = stof(obj[i][1]);
            float v2 = stof(obj[i][2]);
            float v3 = stof(obj[i][3]);
            vertices.push_back({v1, v2, v3});
        }
        if (obj[i][0] == "vn") {
            float v1 = stof(obj[i][1]);
            float v2 = stof(obj[i][2]);
            float v3 = stof(obj[i][3]);
            normal.push_back({v1, v2, v3});
        }
        if (obj[i][0] == "f"){
//
            for(int j = 1; j < obj[i].size(); j++){


                vector<string> face = split(obj[i][j], '/');

                bool hasV = face.size() >= 1;
                bool hasVT = face.size() >= 2;
                bool hasVN = face.size() >= 3;



                Vertex v;









                if(hasV && !hasVT && !hasVN){
                    int vIndex = stoi(face[0]) - 1;

                    //TODO: Calculate Normal for Vertices

                    v = {
                            {vertices[vIndex].x, vertices[vIndex].y, vertices[vIndex].z},

                    };
                }

                if(hasV && hasVT && hasVN) {
                    int vIndex = stoi(face[0]) - 1;
                    int nIndex = stoi(face[2]) - 1;
                    v = {
                            {vertices[vIndex].x, vertices[vIndex].y, vertices[vIndex].z},
                            {normal[nIndex].x,   normal[nIndex].y,   normal[nIndex].z}
                    };
                };

                v.color[0] = 0.8;
                v.color[1] = 0.8;
                v.color[2] = 0.8;


                mesh.push_back( v );


            }

        }




    };



    return mesh;
}



#endif //OPENGLPROJECT_GLOBALS_HPP
