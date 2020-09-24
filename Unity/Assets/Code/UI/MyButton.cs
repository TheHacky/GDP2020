using UnityEngine.EventSystems;
using UnityEngine.UI;
using DG.Tweening;
using UnityEngine;

public class MyButton : Button
{
    public override void OnPointerDown(PointerEventData eventData)
    {
        base.OnPointerDown(eventData);

        transform.DOScale(Vector3.one * 0.9f, 0.1f);
    }

    public override void OnPointerUp(PointerEventData eventData)
    {
        base.OnPointerUp(eventData);
        
        transform.DOScale(Vector3.one * 1.0f, 0.1f);
    }

    public override void OnPointerClick(PointerEventData eventData)
    {
        base.OnPointerClick(eventData);
        
        // implement button click
    }
}
