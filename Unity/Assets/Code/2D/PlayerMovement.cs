using System;
using UnityEngine;

namespace Code._2D
{
    [RequireComponent(typeof(Rigidbody2D), typeof(SpriteRenderer))]
    public class PlayerMovement : MonoBehaviour
    {
        [SerializeField] private float _speed = 5.0f;
        [SerializeField] private float _jumpForce = 20.0f;
        [SerializeField] private Transform _groundCheckTransform = null;
        [SerializeField] private float _groundCheckCircleRadius = 1.0f;
        [SerializeField] private LayerMask _groundCheckLayerMask = 0xffffff;
        private Rigidbody2D _rigidbody2D = null;
        private SpriteRenderer _spriteRenderer = null;

        private bool _isGrounded = false;
        private bool _isJumping = false;
        public bool IsGrounded => _isGrounded;

        private void Awake()
        {
            _rigidbody2D = GetComponent<Rigidbody2D>();
            _spriteRenderer = GetComponent<SpriteRenderer>();
        }

        private void Update()
        {
            _isJumping = _isJumping || Input.GetButtonDown("Jump");
        }

        private void FixedUpdate()
        {
            float horizontal = Input.GetAxis("Horizontal");

            _isGrounded = Physics2D.OverlapCircle(_groundCheckTransform.position, _groundCheckCircleRadius,
                _groundCheckLayerMask);

            _rigidbody2D.velocity = new Vector2(horizontal * _speed, _rigidbody2D.velocity.y);
            _spriteRenderer.flipX = _rigidbody2D.velocity.x < 0.0f ||
                                    !(_rigidbody2D.velocity.x > 0.0f) && _spriteRenderer.flipX;
            // _spriteRenderer.flipX = _rigidbody2D.velocity.x < 0.0f ? true : _rigidbody2D.velocity.x > 0.0f ? false : _spriteRenderer.flipX;
            // if (_rigidbody2D.velocity.x < 0.0f)
            //     _spriteRenderer.flipX = true;
            // else if (_rigidbody2D.velocity.x > 0.0f)
            //     _spriteRenderer.flipX = false;

            if (_isJumping && _isGrounded)
            {
                _rigidbody2D.AddForce(Vector2.up * _jumpForce, ForceMode2D.Impulse);
            }

            _isJumping = false;
        }

        private void OnDrawGizmosSelected()
        {
            if (_groundCheckTransform == null) return;
            
            Gizmos.DrawWireSphere(_groundCheckTransform.position, _groundCheckCircleRadius);
        }
    }
}