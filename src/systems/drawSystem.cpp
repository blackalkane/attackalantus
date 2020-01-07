#include "drawSystem.hpp"
#include "common.hpp"

#include <math.h>
#include <decisionTree.hpp>

DrawSystem::DrawSystem(){

}

DrawSystem::~DrawSystem(){

}

bool DrawSystem::init(){
    return true;
}

void DrawSystem::destroy(){
    System::destroy();
}

void DrawSystem::update(float elapsedMs) {
	for (int i = 0; i < entities.size(); i++) {
		Drawable* drawEntity = dynamic_cast<Drawable*>(entities[i]);
		DrawComponent* drawingObject = drawEntity->getDrawComponent();
		PositionComponent* position = drawEntity->getPositionComponent();
        this->drawUpdateBeforeDraw(position, drawingObject, drawEntity);
		draw(drawingObject, position, projection_2D);
	}
}

void DrawSystem::setProjection(int w, int h, float screen_scale) {
    float left = 0.f;						  // *-0.5;
    float top = 0.f;						  // (float)h * -0.5;
    float right = (float)w / screen_scale;  // *0.5;
    float bottom = (float)h / screen_scale; // *0.5;

    float sx = 2.f / (right - left);
    float sy = 2.f / (top - bottom);
    float tx = -(right + left) / (right - left);
    float ty = -(top + bottom) / (top - bottom);
    projection_2D = {{sx, 0.f, 0.f}, {0.f, sy, 0.f}, {tx, ty, 1.f}};
}

void DrawSystem::Transform::begin()
{
   out = { { 1.f, 0.f, 0.f }, { 0.f, 1.f, 0.f}, { 0.f, 0.f, 1.f} };
}

void DrawSystem::Transform::scale(vec2 scale)
{
   mat3 S = { { scale.x, 0.f, 0.f },{ 0.f, scale.y, 0.f },{ 0.f, 0.f, 1.f } };
   out = mul(out, S);
}

void DrawSystem::Transform::rotate(float radians)
{
   float c = cosf(radians);
   float s = sinf(radians);
   mat3 R = { { c, s, 0.f },{ -s, c, 0.f },{ 0.f, 0.f, 1.f } };
   out = mul(out, R);
}

void DrawSystem::Transform::translate(vec2 offset)
{
   mat3 T = { { 1.f, 0.f, 0.f },{ 0.f, 1.f, 0.f },{ offset.x, offset.y, 1.f } };
   out = mul(out, T);
}

void DrawSystem::Transform::end()
{
   //
}

void DrawSystem::draw(DrawComponent* drawingObject, PositionComponent* position, const mat3& projection){
   // Transformation code, see Rendering and Transformation in the template specification for more info
 // Incrementally updates transformation matrix, thus ORDER IS IMPORTANT
 transform.begin();
 transform.translate(position->getPosition());
 transform.rotate(drawingObject->radian);
 transform.scale(drawingObject->physics.scale);
 transform.end();

 // Setting shaders
 glUseProgram(drawingObject->effect.program);

 // Enabling alpha channel for textures
 glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
 glDisable(GL_DEPTH_TEST);

 // Getting uniform locations for glUniform* calls
 GLint transform_uloc = glGetUniformLocation(drawingObject->effect.program, "transform");
 GLint color_uloc = glGetUniformLocation(drawingObject->effect.program, "fcolor");
 GLint projection_uloc = glGetUniformLocation(drawingObject->effect.program, "projection");

 // Setting vertices and indices
 glBindVertexArray(drawingObject->mesh.vao);
 glBindBuffer(GL_ARRAY_BUFFER, drawingObject->mesh.vbo);
 glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, drawingObject->mesh.ibo);

 // Input data location as in the vertex buffer
 GLint in_position_loc = glGetAttribLocation(drawingObject->effect.program, "in_position");
 GLint in_texcoord_loc = glGetAttribLocation(drawingObject->effect.program, "texcord");
 glEnableVertexAttribArray(in_position_loc);
 glEnableVertexAttribArray(in_texcoord_loc);
 glVertexAttribPointer(in_position_loc, 3, GL_FLOAT, GL_FALSE, sizeof(TexturedVertex), (void*)0);
 glVertexAttribPointer(in_texcoord_loc, 2, GL_FLOAT, GL_FALSE, sizeof(TexturedVertex), (void*)sizeof(vec3));

 // Enabling and binding texture to slot 0
 glActiveTexture(GL_TEXTURE0);
 glBindTexture(GL_TEXTURE_2D, drawingObject->texture->id);

 // Setting uniform values to the currently bound program
 glUniformMatrix3fv(transform_uloc, 1, GL_FALSE, (float*)&transform.out);
 float color[] = { 1.f, 1.f, 1.f };
 glUniform3fv(color_uloc, 1, color);
 glUniformMatrix3fv(projection_uloc, 1, GL_FALSE, (float*)&projection);

 // Drawing!
 glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);
}

void DrawSystem::drawUpdateBeforeDraw(PositionComponent* position, DrawComponent* drawingObject, Drawable* drawEntity){
    // update state
    DecisionTree::updateState(drawEntity->getStateObj(), drawEntity);
    //update sprite to use base on state before draw
    drawEntity->loadStateSprite();
    drawEntity->updateStateFrame();
    // update animation frame
    drawingObject->updateFrame();
    // update direction
    float directionValue = position->getPosX() - position->getPrePosX();
    if (drawEntity->type == EntityType::OTHERS || drawEntity->type == EntityType::GLYPH) {
        return;
    }

    vec2 currentScale = drawingObject->getScale();
    if(directionValue < 0){ // moving left
        drawingObject->setScale({-abs(currentScale.x), currentScale.y});
    }
    else if(directionValue > 0){ // moving right
        drawingObject->setScale({abs(currentScale.x), currentScale.y});
    }
    else{ // idle
        // do nothing
    }

}

std::vector<Entity*> *DrawSystem::getEntityListPointer() {
    return &entities;
}
