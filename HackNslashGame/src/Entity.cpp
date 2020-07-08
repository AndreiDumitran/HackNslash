#include "Entity.h"

const int Entity::DIR_UP = 0, Entity::DIR_DOWN = 1, Entity::DIR_LEFT = 2, Entity::DIR_RIGHT = 3, Entity::DIR_NONE = -1;

void Entity::Update()
{
}

void Entity::Draw()
{
    if (currentFrame != nullptr && active)
        currentFrame->Draw(animSet->spriteSheet, x, y);
    if (solid && Globals::debugging)
    {
        SDL_SetRenderDrawColor(Globals::renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawRect(Globals::renderer, &collisionBox);
    }
}

void Entity::Move(float angle)
{
    moving = true;
    moveSpeed = moveSpeedMax;
    this->angle = angle;

    int newDirection = AngleToDirection(angle);
    if (direction != newDirection)
    {
        direction = newDirection;
        ChangeAnimation(state, false);
    }
}

void Entity::UpdateMovement()
{
    UpdateCollisionBox();
    lastCollisionBox = collisionBox;

    totalXMove = 0;
    totalYMove = 0;

    if (moveSpeed > 0)
    {
        float moveDist = moveSpeed * (TimeController::timeController.dT) * moveLerp;
        if (moveDist > 0)
        {
            // xMove = distance * cos(angle in radians)
            float xMove = moveDist * (cos(angle * Globals::PI / 180));
            // yMove = distance * sin(angle in radians)
            float yMove = moveDist * (sin(angle * Globals::PI / 180));

            x += xMove;
            y += yMove;

            totalXMove = xMove;
            totalYMove = yMove;
            if (!moving)
                moveSpeed -= moveDist;
        }
    }

    if (slideAmount > 0)
    {
        float slideDist = slideAmount * TimeController::timeController.dT * moveLerp;
        if (slideDist > 0)
        {
            float xMove = slideDist * (cos(slideAngle * Globals::PI / 180));
            float yMove = slideDist * (sin(slideAngle * Globals::PI / 180));

            x += xMove;
            y += yMove;

            totalXMove += xMove;
            totalYMove += yMove;
        }
        else slideAmount = 0;
    }
    UpdateCollisionBox();
    SDL_UnionRect(&collisionBox, &lastCollisionBox, &collisionBox);
}

void Entity::UpdateCollisionBox()
{
    collisionBox.x = x - collisionBox.w / 2;
    collisionBox.y = y + collisionBoxYOffset;
    collisionBox.w = collisionBoxW;
    collisionBox.h = collisionBoxH;
}

void Entity::UpdateCollisions()
{
    if (active && collideWithSolids && (moveSpeed > 0 || slideAmount > 0))
    {
        list<Entity*> collisions;

        for (auto entity = Entity::entities.begin(); entity != Entity::entities.end(); entity++)
        {
            if ((*entity)->active && (*entity)->type != this->type && (*entity)->solid && Entity::CheckCollision(collisionBox, (*entity)->collisionBox))
                collisions.push_back(*entity);
        }
        if (collisions.size() > 0)
        {
            UpdateCollisionBox();

            float boxTravelSize = 0;
            if (collisionBox.w < collisionBox.h)
                boxTravelSize = collisionBox.w / 4;
            else
                boxTravelSize = collisionBox.h / 4;

            SDL_Rect sampleBox = lastCollisionBox;
            float movementAngle = Entity::AngleBetweenTwoRects(lastCollisionBox, collisionBox);

            bool foundCollision = false;
            while (!foundCollision)
            {
                SDL_Rect intersection;
                for (auto entity = collisions.begin(); entity != collisions.end(); entity++)
                {
                    if (SDL_IntersectRect(&sampleBox, &(*entity)->collisionBox, &intersection))
                    {
                        foundCollision = true;
                        moveSpeed = 0;
                        moving = false;
                        slideAngle = AngleBetweenTwoEntities((*entity), this);

                        if (intersection.w < intersection.h)
                        {
                            if (lastCollisionBox.x + lastCollisionBox.w / 2 < (*entity)->collisionBox.x + (*entity)->collisionBox.w / 2)
                                sampleBox.x -= intersection.w;
                            else 
                                sampleBox.x += intersection.w;
                        }
                        else
                        {
                            if (lastCollisionBox.y + lastCollisionBox.h / 2 < (*entity)->collisionBox.y + (*entity)->collisionBox.h / 2)
                                sampleBox.y -= intersection.h;
                            else
                                sampleBox.y += intersection.h;
                        }
                    }
                }
                if (foundCollision || (sampleBox.x == collisionBox.x && sampleBox.y == collisionBox.y))
                    break;
                if (DistanceBetweenTwoRect(sampleBox, collisionBox) > boxTravelSize)
                {
                    float xMove = boxTravelSize * (cos(movementAngle * Globals::PI / 180));
                    float yMove = boxTravelSize * (sin(movementAngle * Globals::PI / 180));

                    sampleBox.x += xMove;
                    sampleBox.y += yMove;
                }
                else
                    sampleBox = collisionBox;
            }
            if (foundCollision)
            {
                slideAmount = slideAmount / 2;
                x = sampleBox.x + sampleBox.w / 2;
                y = sampleBox.y - collisionBoxYOffset;
            }
            UpdateCollisionBox();
        }
    }
}

float Entity::DistanceBetweenTwoRect(SDL_Rect& r1, SDL_Rect& r2)
{
    SDL_Point e1, e2;
    e1.x = r1.x + r1.w / 2;
    e1.y = r1.y + r1.y / 2;

    e2.x = r2.x + r2.w / 2;
    e2.y = r2.y + r2.y / 2;

    float distance = abs(sqrt(pow(e2.x - e1.x, 2) + pow(e2.y - e1.y, 2)));
    return distance;
}

float Entity::DistanceBetweenTwoEntities(Entity* e1, Entity* e2)
{
    float distance = abs(sqrt(pow(e2->x - e1->x, 2) + pow(e2->y - e1->y, 2)));
    return distance;
}

float Entity::AngleBetweenTwoEntities(Entity* e1, Entity* e2)
{
    float dx, dy;
    float x1 = e1->x, y1 = e1->y, x2 = e2->x, y2 = e2->y;
    
    dx = x2 - x1;
    dy = y2 - y1;

    return atan2(dy, dx) * 180 / Globals::PI;
}

bool Entity::CheckCollision(SDL_Rect cbox1, SDL_Rect cbox2)
{
    if (SDL_IntersectRect(&cbox1, &cbox2, nullptr))
        return true;
    return false;
}

int Entity::AngleToDirection(float angle)
{
    if ((angle >= 0 && angle <= 45) || angle >= 315 && angle <= 360)
        return DIR_RIGHT;
    else if (angle >= 45 && angle <= 135)
        return DIR_DOWN;
    else if (angle >= 135 && angle <= 225)
        return DIR_LEFT;
    else return DIR_UP;
}

float Entity::AngleBetweenTwoPoints(float cx1, float cy1, float cx2, float cy2)
{
    float dx = cx2 - cx1;
    float dy = cy2 - cy1;

    return atan2(dy, dx) * 180 / Globals::PI;
}

float Entity::AngleBetweenTwoRects(SDL_Rect& r1, SDL_Rect& r2)
{
    float cx1 = r1.x + (r1.w / 2);
    float cy1 = r1.y + (r1.h / 2);

    float cx2 = r2.x + (r2.w / 2);
    float cy2 = r2.y + (r2.h / 2);

    return AngleBetweenTwoPoints(cx1, cy1, cx2, cy2);
}

list<Entity*> Entity::entities;

bool Entity::EntityCompare(const Entity* const& a, const Entity* const& b)
{
    if (a != 0 && b != 0)
        return (a->y < b->y);
    else
        return false;
}

void Entity::RemoveInactiveEntitiesFromList(list<Entity*>* entityList, bool deleteEntities)
{
    for (auto entity = entityList->begin(); entity != entityList->end();)
    {
        if (!(*entity)->active)
        {
            if (deleteEntities)
                delete (*entity);
            entity = entityList->erase(entity);
        }
        else entity++;
    }
}

void Entity::RemoveAllFromList(list<Entity*>* entityList, bool deleteEntities)
{
    for (auto entity = entityList->begin(); entity != entityList->end();)
    {
        if (deleteEntities)
            delete (*entity);
        entity = entityList->erase(entity);
    }
}