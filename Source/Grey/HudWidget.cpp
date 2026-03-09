// Fill out your copyright notice in the Description page of Project Settings.


#include "HudWidget.h"

void UHudWidget::SetSlotIcon(int32 Index, UTexture2D* Icon)
{
    UImage* Slots[10] = { Image0, Image1, Image2, Image3, Image4, Image5, Image6, Image7, Image8, Image9 };

    if (Slots[Index] && Icon)
    {
        Slots[Index]->SetBrushFromTexture(Icon);
    }
}

void UHudWidget::SetItemPreviewText(FText Text)
{
    if (ItemPreview)
    {
        ItemPreview->SetText(Text);
    }
}
