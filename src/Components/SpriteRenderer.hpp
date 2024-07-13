#pragma once
#include "../Component.hpp"
#include "Transform2D.hpp"

class Transform2D;
class GameObject;


class SpriteRenderer : public Component
{
public:
    SpriteRenderer(); 
    ~SpriteRenderer();

    void loadImage(const std::string& filename);
    void resizeImage(int width, int height, bool useNearestNeighbour = false);
    void setImage(const Image& image);
    void setTexture(const Texture2D& texture);
    Image* getImage() { return &image; }
    Texture2D getTexture() const { return texture; }
    void initTexture();

    void setOffset(const Vector2& offset) { this->offset = offset; }
    void setScale(float scale) { this->scale = scale; }
    void setRotation(float rotation) { this->rotation = rotation; }

    void update() override;
    void draw() const;
    void getTransform();
    

protected:
    mutable std::shared_ptr<Transform2D> transform = nullptr;
    float scale = 1.0f;
    Vector2 offset;
    Texture2D texture;
    float rotation = 0.0f;
    Image image;
    Vector2 size;
};

SpriteRenderer::SpriteRenderer(){
    // getTransform();
    texture = {0};
    image = {0};
};

SpriteRenderer::~SpriteRenderer()
{
    UnloadTexture(texture);
}

inline void SpriteRenderer::loadImage(const std::string &filename)
{
    if (image.data)
    {
        UnloadImage(image);
    }
    image = LoadImage(filename.c_str());
}

inline void SpriteRenderer::resizeImage(int width, int height, bool useNearestNeighbour)
{
    if (useNearestNeighbour)
    {
        ImageResizeNN(&image, width, height);
    }
    else
    {
        ImageResize(&image, width, height);
    }

}

inline void SpriteRenderer::setImage(const Image &image)
{
    if (this->image.data)
    {
        UnloadImage(this->image);
    }
    this->image = image;
}

inline void SpriteRenderer::setTexture(const Texture2D &texture)
{
    if (this->texture.id)
    {
        UnloadTexture(this->texture);
    }
    this->texture = texture;
}

inline void SpriteRenderer::initTexture()
{
    if (image.data)
    {
        if (texture.id)
        {
            UnloadTexture(texture);
        }
        texture = LoadTextureFromImage(image);
        size = {static_cast<float>(texture.width), static_cast<float>(texture.height)};
        UnloadImage(image);
    }
    else
    {
        std::cerr << "Image not loaded" << std::endl;
    }
}

void SpriteRenderer::update()
{
    if (!isActive)
    {
        return;
    }
    if (!transform)
    {
        getTransform();
    }
    if (!texture.id)
    {
        initTexture();
    }
    draw();
}

void SpriteRenderer::draw() const
{
    if (transform) {
        Vector2 position = transform->getGamePosition();
        float worldRotation = transform->getWorldRotation();
        float worldScale = transform->getWorldScale();

        DrawTextureEx(texture, position + offset - size * scale *worldScale / 2,worldRotation+rotation,scale, {255,255,255,255});
    } else {
        std::cerr << "Transform not available for drawing." << std::endl;
    }
}

void SpriteRenderer::getTransform()
{
    if (!owner)
    {
        std::cerr << "owner not found" << std::endl;
        return;
    }
    transform = owner->getComponent<Transform2D>();
    if (!transform)
    {
        transform = owner->addComponent<Transform2D>();
    }
}
