#include "StateBlue.hpp"

namespace CoF {
    extern const GLchar* const StateDataTemplate<StateEnum::Blue>::vs;
    extern const GLchar* const StateDataTemplate<StateEnum::Blue>::fs;

    ////////////////////////////////
    /// StateBlue::Init()        ///
    ////////////////////////////////
    template<> void StateTemplate<StateEnum::Blue>::Init() {
        Log::Info("StateBlue::Init()");
        glClearColor(0.0, 0.0, 1.0, 1.0);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        //glEnable(GL_BLEND);
        //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        std::list<BnD::Vec<GLfloat>> v;
        std::list<BnD::Vec<GLfloat>> vn;
        std::list<BnD::Vec<GLuint>> f;
        std::map<std::array<GLuint, 3>, GLuint> vertices;
        std::map<std::array<GLuint, 3>, GLuint>::iterator it;
        std::ifstream fin("./data/test1.obj");
        BnD::Vec<GLfloat> temp_v, temp_vn;
        BnD::Vec<GLuint> temp_f;
        std::array<GLuint, 3> temp_vertex;
        std::string str, temp_str;
        std::stringstream ss;

        while(std::getline(fin, str).good()) {
            ss.clear();
            ss.str(str);
            ss>>temp_str;
            if(temp_str == "#") Log::Info("Comment: %s", ss.str().c_str());
            else if(temp_str == "v") {
                ss>>temp_v.x()>>temp_v.y()>>temp_v.z();
                v.push_back(temp_v);
            } else if(temp_str == "vn") {
                ss>>temp_vn.x()>>temp_vn.y()>>temp_vn.z();
                vn.push_back(temp_vn);
            } else if(temp_str == "f") {
                for(uint8_t r = 0; r < 3; r++) {
                    for(uint8_t i = 0; i < 3; i++) {
                        ss>>temp_vertex[i];
                        ss.clear();
                        if(ss.get() != '/') break;
                    }
                    if((it = vertices.find(temp_vertex)) != vertices.end()) temp_f[r] = it->second;
                    else {
                        temp_f[r] = vertices.size();
                        vertices.insert(std::pair<std::array<GLuint, 3>, GLuint>(temp_vertex, temp_f[r]));
                    }
                }
                f.push_back(temp_f);
            } else if(temp_str == "") {

            }
        }

        ////////////////////////////////////
        /// Mat info
        //Mat4 temp = Mat4::IdentityMat();
        //for(size_t c = 0; c < 4; c++)
            //for(size_t r = 0; r < 4; r++)
                //Log::Info("Mat4::Identity()[%zu][%zu] = %f", c, r, temp.v[c][r]);
        //Log::Info("Size: %zu", Mat4::get(BnD::BuildIndices<4>{}, BnD::BuildIndices<4>{}}).size());
        //for(size_t i = 0; i < 4; i++) {
            //for(size_t r = 0; r < 4; r++)
            //Log::Info("Identity[%zu][%zu]: %f", i, r, Mat4::IdentityMat().v[i][r]);
        //}
        Log::Info("is_pod(Mat4): %s", std::is_pod<BnD::Mat<GLfloat>>::value ? "true" : "false");
        Log::Info("is_pod(Vec): %s", std::is_pod<BnD::Vec<int, 5>>::value ? "true" : "false");
        Log::Info("is_pod(Mat): %s", std::is_pod<BnD::Mat<int, 5, 6>>::value ? "true" : "false");
        Log::Info("sizeof(Mat): %zu", sizeof(BnD::Mat<GLfloat>));

        std::vector<BnD::Vec<GLfloat>> vv(v.begin(), v.end());
        std::vector<BnD::Vec<GLfloat>> vvn(vn.begin(), vn.end());

        self.mesh.vertexCount = vertices.size();
        self.mesh.faceCount = f.size();
        self.mesh.vertices = new Mesh3D<BnD::Mesh::NORMALS>::Vertex[self.mesh.vertexCount];
        self.mesh.faces = new Mesh3D<BnD::Mesh::NORMALS>::Face[self.mesh.faceCount];
        Log::Info("vertexCount: %u, faceCount: %u, normals: %u", self.mesh.vertexCount, self.mesh.faceCount, vn.size());
        for(it = vertices.begin(); it != vertices.end(); it++) {
            self.mesh.vertices[it->second][0] = vv[it->first[0] - 1];
            self.mesh.vertices[it->second][1] = vvn[it->first[2] - 1];
        }
        size_t i = 0;
        for(std::list<BnD::Vec<GLuint, 3>>::iterator it = f.begin(); it != f.end(); it++, i++)
            self.mesh.faces[i] = *it;

        self.matM.Identity();
        self.matV.Identity();
        self.matV.Move(0, 800.0f).Move(1, 450.0f);
        self.matV.Scale(0, 100.0f).Scale(1, 100.0f).Scale(2, 1.0f);
        //GLIdentity(self.matM);
        //GLScale(self.matM, 2.0, 2.0, 2.0);

        self.GLProgram = NewGLProgram(self.vs, self.fs);
        glUseProgram(self.GLProgram);
        self.iVec3Vertex = glGetAttribLocation(self.GLProgram, "iVec3Vertex");
        self.iVec3Normal = glGetAttribLocation(self.GLProgram, "iVec3Normal");
        self.uMat4P = glGetUniformLocation(self.GLProgram, "uMat4P");
        self.uMat4V = glGetUniformLocation(self.GLProgram, "uMat4V");
        self.uMat4M = glGetUniformLocation(self.GLProgram, "uMat4M");

        glUniformMatrix4fv(self.uMat4P, 1, GL_FALSE, &global.matP);
        glUniformMatrix4fv(self.uMat4V, 1, GL_FALSE, &self.matV);
        glUniformMatrix4fv(self.uMat4M, 1, GL_FALSE, &self.matM);

        glGenVertexArrays(1, &self.VAO);
        glBindVertexArray(self.VAO);

        glGenBuffers(1, &self.VBOVertex);
        glBindBuffer(GL_ARRAY_BUFFER, self.VBOVertex);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Mesh3D<BnD::Mesh::NORMALS>::Vertex) * self.mesh.vertexCount, self.mesh.vertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(self.iVec3Vertex);
        glVertexAttribPointer(self.iVec3Vertex, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(BnD::Vec<GLfloat>), (GLvoid*)0);
        glEnableVertexAttribArray(self.iVec3Normal);
        glVertexAttribPointer(self.iVec3Normal, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(BnD::Vec<GLfloat>), (GLvoid*)sizeof(BnD::Vec<GLfloat>));

        glGenBuffers(1, &self.VBOIndex);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, self.VBOIndex);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Mesh3D<BnD::Mesh::NORMALS>::Face) * self.mesh.faceCount, self.mesh.faces, GL_STATIC_DRAW);

        glBindVertexArray(0);
        glUseProgram(0);

        self.inputFlags = StateData::InputFlags::None;
    }

    ////////////////////////////////
    /// StateBlue::Quit()        ///
    ////////////////////////////////
    template<> void StateTemplate<StateEnum::Blue>::Quit() {
        Log::Info("StateBlue::Quit()");

        glDeleteBuffers(1, &self.VBOVertex);
        glDeleteBuffers(1, &self.VBOIndex);
        glDeleteVertexArrays(1, &self.VAO);
        glDeleteProgram(self.GLProgram);

        delete[] self.mesh.vertices;
        delete[] self.mesh.faces;
    }

    ////////////////////////////////
    /// StateBlue::Tick()        ///
    ////////////////////////////////
    template<> void StateTemplate<StateEnum::Blue>::Tick() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(self.GLProgram);

        //self.matM.Identity();
        //self.matM.Rotate(0, 0.01f);//.Rotate(1, self.rY);
        BnD::Mat<GLfloat> temp;
        temp.Identity().Rotate(1, 0.01f);
        self.matM = self.matM * temp;
        //self.matM.Rotate(1, 0.01f);
        //self.matM.Rotate(1, 0.5f);
        glUniformMatrix4fv(self.uMat4M, 1, GL_FALSE, &self.matM);

        if(self.inputFlags & StateData::InputFlags::ArrowUp) self.matV.Rotate(0, 0.01f);
        if(self.inputFlags & StateData::InputFlags::ArrowDown) self.matV.Rotate(0, -0.01f);
        if(self.inputFlags & StateData::InputFlags::ArrowRight) self.matV.Rotate(1, 0.01f);
        if(self.inputFlags & StateData::InputFlags::ArrowLeft) self.matV.Rotate(1, -0.01f);
        //self.matV.Rotate(2, 0.15f);
        glUniformMatrix4fv(self.uMat4V, 1, GL_FALSE, &self.matV);

        glBindVertexArray(self.VAO);
        glBindBuffer(GL_ARRAY_BUFFER, self.VBOVertex);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, self.VBOIndex);
        glDrawElements(GL_TRIANGLES, self.mesh.faceCount * 3, GL_UNSIGNED_INT, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        //glUseProgram(0);

        while(SDL_PollEvent(&global.event)) {
            switch(global.event.type)
            {
            case SDL_KEYDOWN:
                switch(global.event.key.keysym.sym) {
                case SDLK_UP:
                    self.inputFlags |= StateData::InputFlags::ArrowUp;
                    break;
                case SDLK_DOWN:
                    self.inputFlags |= StateData::InputFlags::ArrowDown;
                    break;
                case SDLK_RIGHT:
                    self.inputFlags |= StateData::InputFlags::ArrowRight;
                    break;
                case SDLK_LEFT:
                    self.inputFlags |= StateData::InputFlags::ArrowLeft;
                    break;
                }
                break;
            case SDL_KEYUP:
                switch(global.event.key.keysym.sym) {
                case SDLK_UP:
                    self.inputFlags ^= self.inputFlags & StateData::InputFlags::ArrowUp;
                    break;
                case SDLK_DOWN:
                    self.inputFlags ^= self.inputFlags & StateData::InputFlags::ArrowDown;
                    break;
                case SDLK_RIGHT:
                    self.inputFlags ^= self.inputFlags & StateData::InputFlags::ArrowRight;
                    break;
                case SDLK_LEFT:
                    self.inputFlags ^= self.inputFlags & StateData::InputFlags::ArrowLeft;
                    break;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                switch(global.event.button.button) {
                case SDL_BUTTON_LEFT:
                    self.inputFlags |= StateData::InputFlags::MouseLeft;
                    break;
                case SDL_BUTTON_RIGHT:
                    self.inputFlags |= StateData::InputFlags::MouseRight;
                    break;
                case SDL_BUTTON_MIDDLE:
                    self.inputFlags |= StateData::InputFlags::MouseMiddle;
                    break;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                switch(global.event.button.button) {
                case SDL_BUTTON_LEFT:
                    self.inputFlags ^= self.inputFlags & StateData::InputFlags::MouseLeft;
                    break;
                case SDL_BUTTON_RIGHT:
                    self.inputFlags ^= self.inputFlags & StateData::InputFlags::MouseRight;
                    break;
                case SDL_BUTTON_MIDDLE:
                    self.inputFlags ^= self.inputFlags & StateData::InputFlags::MouseMiddle;
                    break;
                }
                break;
            case SDL_MOUSEMOTION:
                break;
            case SDL_QUIT:
                SwitchState(StateEnum::QUIT);
                return;
            }
        }
    }
}
