using System;
using UnityEngine;
using UnityEngine.AI;

namespace Code
{
    [RequireComponent(typeof(NavMeshAgent))]
    public class Navigation : MonoBehaviour
    {
        private NavMeshAgent _navMeshAgent = null;

        private void Awake()
        {
            _navMeshAgent = GetComponent<NavMeshAgent>();
        }

        // static nav mesh agent destination set
        // private void Start()
        // {
        //     _navMeshAgent.SetDestination(transform.position + Vector3.right * 30 + Vector3.forward * 30);
        // }

        private void Update()
        {
            if (Input.GetMouseButtonDown(0)) // left mouse button
            {
                Ray mouse = Camera.main.ScreenPointToRay(Input.mousePosition);
                RaycastHit hit;
                if (Physics.Raycast(mouse, out hit))
                {
                    _navMeshAgent.SetDestination(hit.point);
                }
            }
        }
    }
}