using System;
using System.Collections;
using System.Collections.Generic;
using Code.Data;
using UnityEngine;
using UnityEngine.UI;

public class Enemy : MonoBehaviour
{
    [SerializeField] private float _maxHealth = 100.0f;
    [SerializeField] private float _damage = 30.0f;
    [SerializeField] private Image _healthBarFilling = null;
    [SerializeField] private Transform _healthBarCanvas = null;
    [SerializeField] private CameraReference _camera = null;

    private float _actualHealth = 0.0f;

    private void Awake()
    {
        _actualHealth = _maxHealth;
    }

    private void Update()
    {
        // _healthBarCanvas.LookAt(_camera.value.transform, Vector3.up);

        // Vector3 cameraPosition = _camera.value.transform.position;
        // cameraPosition.y = _healthBarCanvas.position.y;
        // _healthBarCanvas.forward = cameraPosition - _healthBarCanvas.position;

        Vector3 cameraDirection = _healthBarCanvas.InverseTransformPoint(_camera.value.transform.position);
        float angle = Mathf.Atan2(cameraDirection.x, cameraDirection.z);
        _healthBarCanvas.Rotate(_healthBarCanvas.up, angle * Mathf.Rad2Deg);
        
    }

    private void OnCollisionEnter(Collision other)
    {
        _actualHealth -= _damage;
        _healthBarFilling.fillAmount = _actualHealth / _maxHealth;
    }
}
