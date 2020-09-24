using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Enemy : MonoBehaviour
{
    [SerializeField] private float _maxHealth = 100.0f;
    [SerializeField] private float _damage = 30.0f;
    [SerializeField] private Image _healthBarFilling = null;

    private float _actualHealth = 0.0f;

    private void Awake()
    {
        _actualHealth = _maxHealth;
    }

    private void OnCollisionEnter(Collision other)
    {
        _actualHealth -= _damage;
        _healthBarFilling.fillAmount = _actualHealth / _maxHealth;
    }
}
