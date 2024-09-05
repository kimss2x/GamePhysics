#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#define _USE_MATH_DEFINES
#include <math.h>

// 파티클 구조체
struct Particle {
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Color color;
    float lifetime;
};

// 파티클 생성 함수
void createParticles(std::vector<Particle>& particles, int count, sf::Vector2f position, float velocity, float angle) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 360);

    for (int i = 0; i < count; ++i) {
        float angleRad = (angle + dis(gen)) * M_PI / 180.0f;
        sf::Vector2f velocityVec(velocity * cos(angleRad), velocity * sin(angleRad));
        sf::Color randomColor(rand() % 255, rand() % 255, rand() % 255);
        particles.push_back({ position, velocityVec, randomColor, 5.0f });
    }
}

// 파티클 업데이트 함수 (중력 가속도 적용)
void updateParticles(std::vector<Particle>& particles, float deltaTime, float gravity, float timeScale) {
    for (auto& p : particles) {
        p.velocity.y += gravity * deltaTime * timeScale;  // 중력 가속도 적용
        p.position += p.velocity * deltaTime;  // 속도에 따른 위치 변화
        p.lifetime -= deltaTime;  // 파티클 수명 감소
    }
    // 수명이 다한 파티클 제거
    particles.erase(std::remove_if(particles.begin(), particles.end(), [](Particle& p) { return p.lifetime <= 0.0f; }), particles.end());
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Particle System");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);

    std::vector<Particle> particles;
    sf::Clock deltaClock;

    // 기본값 설정
    int particleCount = 100;
    float initialVelocity = 200.0f;
    float gravity = 9.8f;
    float angle = 0.0f;
    float timeScale = 100.0f;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        float deltaTime = deltaClock.restart().asSeconds();
        ImGui::SFML::Update(window, sf::seconds(deltaTime));

        // ImGui UI
        ImGui::Begin("Particle Settings");
        ImGui::SliderInt("Particle Count", &particleCount, 10, 500);
        ImGui::SliderFloat("Velocity", &initialVelocity, 0.0f, 1000.0f);
        ImGui::SliderFloat("Gravity", &gravity, 0.0f, 1000.0f);  // 중력값 조절 가능
        ImGui::SliderFloat("Angle", &angle, 0.0f, 360.0f);
        if (ImGui::Button("Create Particle Explosion")) {
            createParticles(particles, particleCount, sf::Vector2f(400, 300), initialVelocity, angle);
        }
        ImGui::End();

        // 파티클 업데이트 (중력 추가)
        updateParticles(particles, deltaTime, gravity, timeScale);

        // 파티클을 화면에 그리기
        window.clear();
        for (const auto& p : particles) {
            sf::CircleShape particleShape(3.0f);
            particleShape.setPosition(p.position);
            particleShape.setFillColor(p.color);
            window.draw(particleShape);
        }

        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}
