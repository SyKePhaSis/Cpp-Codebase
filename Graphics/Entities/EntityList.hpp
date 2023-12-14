#pragma once

#include "../Core/Config.hpp"
#include "../Core/TextureLoader.hpp"

#include "Entity.hpp"
#include "Character.hpp"

#include <vector>
#include <memory>
#include <fstream>
#include <string>

class EntityList {
    public:
        int eidcounter; // Id Handler Counter
        std::vector<std::shared_ptr<Entity>> list;
        std::vector<Collisions::Border>* bv;
        std::shared_ptr<TextureList> tl;
        std::shared_ptr<Config> conf;

        EntityList(void)
        : eidcounter(0) {}

        EntityList(std::vector<Collisions::Border>* bvp, TextureList& tlp, Config& config)
        {
            this->AttachAll(bvp, tlp, config);
        }

        void AttachAll(std::vector<Collisions::Border>* bvp, TextureList& tlp, Config& config)
        {
            this->AttachBordersVector(bvp);
            this->AttachTextureList(tlp);
            this->AttachConfig(config);
        }
        void AttachBordersVector(std::vector<Collisions::Border>* bvp)
        {
            bv = bvp;
        }

        void AttachTextureList(TextureList &tlp)
        {
            tl = std::make_shared<TextureList>(tlp);
        }

        void AttachConfig(Config& config)
        {
            conf = std::make_shared<Config>(config);
        }


        void AddEntity(std::shared_ptr<Entity> e)
        {
            e->changeId(eidcounter);
            list.push_back(e);
            eidcounter++;
        }

        void LoadEntitiesFromFile(std::string path)
        {
            if(!bv || !tl.get())
            {
                printf("ERROR: Border Vector Or Texture List is not Attached And Cannot Load EntitiesFromFile");
            } else {

            }
            std::fstream dfile(path);
            if(dfile)
            {
                printf("INFO: Successfully Oppened Entity File [%s]\n", path.c_str());
                //Counter
                int c = 0;

                //Entity Identification
                int eid;
                std::string ename;

                //Position And Size
                Vector2 epos;
                Vector2 esize;

                //Character Texture
                std::string etextpath;

                //Character Animation
                std::string capath;

                //Selector
                std::string selpath;

                while(dfile >> eid >> ename >> epos.x >> epos.y >> esize.x >> esize.y >> etextpath >> capath >> selpath)
                {
                    c++;
                    switch(eid)
                    {
                        case 0:
                        {
                            std::shared_ptr<Entity> e = std::make_shared<Entity>(ename, esize, tl, etextpath, bv);
                            e->LoadAnimationsFromFile(capath);
                            e->AttachEntitySelector(selpath);
                            e->pos = epos;
                            this->AddEntity(e);
                            break;
                        }

                        case 1:
                        {
                            std::shared_ptr<Character> c = std::make_shared<Character>(ename, esize, tl, etextpath, bv, conf.get());
                            c->LoadAnimationsFromFile(capath);
                            c->AttachEntitySelector(selpath);
                            c->pos = epos;
                            this->AddEntity(c);
                            break;
                        }
                    }
                }
                printf("INFO: Added a Total of [%d] Entities\n", c);

            } else {
                printf("INFO: Couldn't Open EntityList File [%s]\n", path.c_str());
            }
        }

        void Update(void)
        {
            for(auto& entity: list)
            {
                entity->Update();
            }
        }

        void Render(void)
        {
            for(auto& entity: list)
            {
                entity->Render();
            }
        }
};
