#include <iostream>

#include "grapi/runtime/display_object.h"
#include "grapi/runtime/transform.h"
#include "grapi/runtime/input_state.h"
#include "grapi/runtime/utils.h"
#include "grapi/runtime/animation_clip.h"
#include "Cluster.h"

#define NOMINMAX
#include <windows.h>

Cluster::Cluster(const grapi::base::String& id, const grapi::base::TypeInfo* type_info) : grapi::runtime::Action(id, type_info) {
}

Cluster::~Cluster() {
}

void Cluster::setupCluster() {
    // 모드별 오브젝트 찾기 (Normal만 씬에서 "Nomal"로 잘못 표기됨)
    ecoMode = grapi::runtime::findObjectByName("Eco");
    normalMode = grapi::runtime::findObjectByName("Nomal");
    sportMode = grapi::runtime::findObjectByName("Sport");

    if (ecoMode) {
        ecoMode->setVisible(false);
        ecoModeAnimator = ecoMode->getComponent<grapi::runtime::Animator>();
    }
    if (normalMode) {
        normalMode->setVisible(false);
        normalModeAnimator = normalMode->getComponent<grapi::runtime::Animator>();
    }
    if (sportMode) {
        sportMode->setVisible(true);
        sportModeAnimator = sportMode->getComponent<grapi::runtime::Animator>();
    }
}

void Cluster::start() {
    setupCluster();
    updateMode();

    // 초기 모드에 맞는 intro 재생
    if (currentMode == 0 && ecoModeAnimator) {
        grapi::runtime::AnimationClip* clip = ecoModeAnimator->getClipByName("eco_intro");
        if (clip) {
            ecoModeAnimator->stop();
            clip->setClampWhenFinished(true);
            ecoModeAnimator->play("eco_intro");
        }
    } else if (currentMode == 1 && normalModeAnimator) {
        grapi::runtime::AnimationClip* clip = normalModeAnimator->getClipByName("normal_intro");
        if (clip) {
            normalModeAnimator->stop();
            clip->setClampWhenFinished(true);
            normalModeAnimator->play("normal_intro");
        }
    } else if (currentMode == 2 && sportModeAnimator) {
        grapi::runtime::AnimationClip* clip = sportModeAnimator->getClipByName("sport_intro");
        if (clip) {
            sportModeAnimator->stop();
            clip->setClampWhenFinished(true);
            sportModeAnimator->play("sport_intro");
        }
    }
}

void Cluster::update(const vfloat delta_time) {
    // m 키: 모드 전환 (0 -> 1 -> 2 -> 0 ...)
    bool curr_m = (GetAsyncKeyState('M') & 0x8000) != 0;
    if (curr_m && !prev_m_) {
        int nextMode = (currentMode + 1) % 3;
        changeMode(nextMode);
        std::cout << "Cluster Mode: " << (nextMode == 0 ? "Eco" : nextMode == 1 ? "Normal" : "Sport") << std::endl;
    }
    prev_m_ = curr_m;

    updateModeTransition(delta_time);
}

void Cluster::changeMode(int newMode) {
    if (newMode == currentMode) return;

    previousMode = currentMode;
    currentMode = newMode;
    modeTransitionTimer = 0.0;
    isTransitioning = true;

    // Eco(0)로 전환
    if (currentMode == 0) {
        if (previousMode == 2 && sportModeAnimator) {
            grapi::runtime::AnimationClip* outroClip = sportModeAnimator->getClipByName("sport_outro");
            if (outroClip) {
                sportModeAnimator->stop();
                outroClip->setClampWhenFinished(true);
                sportModeAnimator->play("sport_outro");
            }
        }
        if (ecoModeAnimator) {
            grapi::runtime::AnimationClip* clip = ecoModeAnimator->getClipByName("eco_intro");
            if (clip) {
                ecoModeAnimator->stop();
                clip->setClampWhenFinished(true);
                ecoModeAnimator->play("eco_intro");
            }
        }
    }

    // Normal(1)로 전환
    if (currentMode == 1) {
        if (previousMode == 0) {
            if (ecoModeAnimator) {
                grapi::runtime::AnimationClip* outroClip = ecoModeAnimator->getClipByName("eco_outro");
                if (outroClip) {
                    ecoModeAnimator->stop();
                    outroClip->setClampWhenFinished(true);
                    ecoModeAnimator->play("eco_outro");
                }
            }
            if (normalModeAnimator) {
                grapi::runtime::AnimationClip* clip = normalModeAnimator->getClipByName("normal_intro");
                if (clip) {
                    normalModeAnimator->stop();
                    clip->setClampWhenFinished(true);
                    normalModeAnimator->play("normal_intro");
                }
            }
        }
    }

    // Sport(2)로 전환
    if (currentMode == 2) {
        if (previousMode == 1 && sportModeAnimator) {
            if (ecoModeAnimator) ecoModeAnimator->stop();
            if (normalModeAnimator) normalModeAnimator->stop();
            sportModeAnimator->stop();
            grapi::runtime::AnimationClip* clip = sportModeAnimator->getClipByName("sport_intro");
            if (clip) {
                clip->setClampWhenFinished(true);
                sportModeAnimator->play("sport_intro");
            }
        }
    }
}

void Cluster::updateMode() {
    if (isTransitioning) return;

    if (ecoMode) {
        ecoMode->setVisible(true);
        ecoMode->setOpacity(currentMode == 0 ? 1.0f : 0.0f);
    }
    if (normalMode) {
        normalMode->setVisible(true);
        normalMode->setOpacity(currentMode == 1 ? 1.0f : 0.0f);
    }
    if (sportMode) {
        sportMode->setVisible(true);
        sportMode->setOpacity(currentMode == 2 ? 1.0f : 0.0f);
    }
}

void Cluster::updateModeTransition(const vfloat delta_time) {
    if (!isTransitioning) return;

    modeTransitionTimer += delta_time;
    if (modeTransitionTimer >= modeTransitionDuration) {
        modeTransitionTimer = modeTransitionDuration;
        isTransitioning = false;
    }

    float t = static_cast<float>(modeTransitionTimer / modeTransitionDuration);
    float progress = t < 0.5f
        ? 2.0f * t * t
        : 1.0f - 2.0f * (1.0f - t) * (1.0f - t);

    float oldOpacity = 1.0f - progress;
    float newOpacity = progress;

    if (ecoMode) ecoMode->setVisible(true);
    if (normalMode) normalMode->setVisible(true);
    if (sportMode) sportMode->setVisible(true);

    if (previousMode == 0 && ecoMode) ecoMode->setOpacity(oldOpacity);
    if (previousMode == 1 && normalMode) normalMode->setOpacity(oldOpacity);
    if (previousMode == 2 && sportMode) sportMode->setOpacity(oldOpacity);

    if (currentMode == 0 && ecoMode) ecoMode->setOpacity(newOpacity);
    if (currentMode == 1 && normalMode) normalMode->setOpacity(newOpacity);
    if (currentMode == 2 && sportMode) sportMode->setOpacity(newOpacity);

    for (int i = 0; i < 3; i++) {
        if (i != previousMode && i != currentMode) {
            if (i == 0 && ecoMode) ecoMode->setOpacity(0.0f);
            if (i == 1 && normalMode) normalMode->setOpacity(0.0f);
            if (i == 2 && sportMode) sportMode->setOpacity(0.0f);
        }
    }

    if (!isTransitioning) {
        if (ecoMode) ecoMode->setOpacity(currentMode == 0 ? 1.0f : 0.0f);
        if (normalMode) normalMode->setOpacity(currentMode == 1 ? 1.0f : 0.0f);
        if (sportMode) sportMode->setOpacity(currentMode == 2 ? 1.0f : 0.0f);
    }
}
