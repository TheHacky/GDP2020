using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(CharacterController))]
public class PlayerMovement : MonoBehaviour
{
    [SerializeField] private float _speed = 10.0f;
    [SerializeField] private float _rotationSpeed = 60.0f;

    private CharacterController _controller = null;
    private Camera _camera = null;
    
    private void Awake()
    {
        _controller = GetComponent<CharacterController>();
        _camera = GetComponentInChildren<Camera>();
    }

    private void Start()
    {
    }

    private void FixedUpdate()
    {
        float h = Input.GetAxis("Horizontal");
        float v = Input.GetAxis("Vertical");
        float mouseX = Input.GetAxis("Mouse X");
        float mouseY = Input.GetAxis("Mouse Y");
        
        transform.Rotate(Vector3.up, mouseX * _rotationSpeed * Time.deltaTime);
        _camera.transform.Rotate(Vector3.right, mouseY * _rotationSpeed * Time.deltaTime);
        
        Vector3 move = new Vector3(h, 0.0f, v) * _speed;
        _controller.SimpleMove(transform.TransformDirection(move));
    }

    private void Update()
    {
    }

    private void LateUpdate()
    {
    }
}