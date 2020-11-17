using System;
using System.Collections;
using System.Collections.Generic;
using Code.Data;
using UnityEngine;

[RequireComponent(typeof(CharacterController))]
public class PlayerMovement : MonoBehaviour
{
    [SerializeField] private float _speed = 10.0f;
    [SerializeField] private float _rotationSpeed = 60.0f;
    [SerializeField] private float _maximumCameraAngle = 30.0f;
    [SerializeField] private float _gravity = -10.0f;
    [SerializeField] private float _jumpForce = 20.0f;
    [SerializeField] private CameraReference _cameraReference = null;

    private CharacterController _controller = null;
    private Camera _camera = null;
    private float _actualCameraRotation = 0.0f;
    private float _ySpeed = 0.0f;
    private bool _isJumping = false;

    private void Awake()
    {
        _controller = GetComponent<CharacterController>();
        _camera = GetComponentInChildren<Camera>();
        _cameraReference.value = _camera;
    }

    private void Start()
    {
        Cursor.lockState = CursorLockMode.Locked;
    }

    private void FixedUpdate()
    {
        float h = Input.GetAxis("Horizontal");
        float v = Input.GetAxis("Vertical");
        float mouseX = Input.GetAxis("Mouse X");
        float mouseY = Input.GetAxis("Mouse Y");

        transform.Rotate(Vector3.up, mouseX * _rotationSpeed * Time.deltaTime);

        float rot = mouseY * _rotationSpeed * Time.deltaTime;
        if (Mathf.Abs(_actualCameraRotation + rot) < _maximumCameraAngle)
        {
            _camera.transform.Rotate(Vector3.right, rot);
            _actualCameraRotation += rot;
        }

        if (_controller.isGrounded)
        {
            _ySpeed = _isJumping ? _jumpForce : 0.0f;
        }
        else
        {
            _ySpeed += _gravity * Time.deltaTime;
        }

        _isJumping = false;

        Vector3 move = new Vector3(h, _ySpeed, v) * (_speed * Time.deltaTime);
        _controller.Move(transform.TransformDirection(move));
    }

    private void Update()
    {
        _isJumping = _isJumping || Input.GetButtonDown("Jump");
    }

    private void LateUpdate()
    {
    }
}